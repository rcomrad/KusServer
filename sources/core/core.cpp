#include "core.hpp"

#include <fstream>

#include "domain/error_message.hpp"

#include "database/connection_manager.hpp"

#include "file/file_router.hpp"
#include "post/journal_handler.hpp"
#include "post/plan_handler.hpp"
#include "post/user_handler.hpp"
#include "tester/tester.hpp"

#include "generate_code.hpp"
#include "program_state.hpp"
#include "server.hpp"
#include "submission_queue.hpp"

//--------------------------------------------------------------------------------

core::Core::Core() noexcept
{
    generateDatabaseStructuresFiles();
    auto& state     = ProgramState::getInstance();
    mApps["server"] = std::move(std::thread(&Core::serverThread, this));
    if (state.checkFlag(Flag::SUB_CHECK))
        mApps["tester"] = std::move(std::thread(&Core::testerThread, this));
}

void
core::Core::remakeDatabase()
{
    createEnvironment();
    createDatabaseFromFile("database.psql_db");
    post::PostHandler::uploadFromFile("database.dmp");
}

void
core::Core::populate()
{
    post::PostHandler::uploadFromFile("../tests/example.dmp");

    post::PostHandler::uploadFromFile("../tests/user.data");

    post::PostHandler::uploadFromFile("../tests/plan_test.csv");
    post::PostHandler::uploadFromFile("../tests/plan_cpp.csv");

    post::PostHandler::uploadFromFile("../tests/journal.data");
}

void
core::Core::run(const std::vector<std::string>& argv) noexcept
{
    // mCommand.process(argv);

    // std::map<Command::Type, std::function<void()>> methodMap{
    //     {Command::Type::GET_USERS,           [&]() { printUsers(); }       },
    //     {Command::Type::GET_ACTIVE_USERS,    [&]() { printUsers(); }       },
    //     {Command::Type::GET_DELETED_USERS,   [&]() { printUsers(); }       },
    //     {Command::Type::RENAME_USERS,        [&]() { renameUsers(); }      },
    //     {Command::Type::GENERATE_NAMES,      [&]() { generateNames(); }    },
    //     {Command::Type::GENERATE_ROBO_NAMES, [&]() { generateRoboNames(); }},
    //     {Command::Type::EVALUATE,            [&]() { getResults(); }       }
    // };

    auto& state = ProgramState::getInstance();

    bool flag = true;
    while (true)
    {
        if (state.needRestart())
        {
            state.startRestart();
            if (state.needRemakeDB()) remakeDatabase();
            if (state.needPopulateDB()) populate();
            if (state.needReloadSubmitions())
            {
                SubmissionQueue::getInstance().reload();
            }

            state.endRestart();
        }
    }
}

void
core::Core::serverThread() noexcept
{
    Server app;
    while (true)
        ;
}

void
core::Core::testerThread() noexcept
{
    auto& state = ProgramState::getInstance();
    auto& sub   = SubmissionQueue::getInstance();
    while (true)
    {

        if (!sub.isEmpty())
        {
            std::cout << "start_checking\n";
            test::Tester tester(state.getValue(Value::TEST_THRD));
            tester.run(sub.get());
            std::cout << "end_checking\n";
        }
    }
}

void
core::Core::createDatabaseFromFile(std::string aFileName) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();

    std::vector<data::ColumnSetting> colums;
    std::ifstream ios(aFileName);
    if (!ios.is_open())
    {
        std::cout << "NO_SUCH_FILE!\n";
        return;
    }
    else
    {
        std::cout << "Extracting_file\n";
    }
    std::string s1, s2;
    std::string name;
    while (ios >> s1)
    {
        std::getline(ios, s2, ' ');
        std::getline(ios, s2);
        if (s1 == "TABLE")
        {
            if (name.size()) connection.val.createTable(name, colums);
            colums.clear();
            name = s2;
        }
        else
        {
            colums.emplace_back(s1, s2);
        }
    }
}

void
core::Core::createEnvironment() noexcept
{
    data::ConnectionManager::turnOff();
    {
        auto connection = data::ConnectionManager::getAdminConnection();
        connection.val.dropDatabase(data::ConnectionType::USER);
    }
    {
        auto connection = data::ConnectionManager::getAdminConnection();
        connection.val.createEnvironment(data::ConnectionType::USER);
    }
    data::ConnectionManager::turnOn();
}
