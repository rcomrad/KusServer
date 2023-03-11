#include "core.hpp"

// #include <fstream>
// #include <functional>
// #include <map>
// #include <set>

#include "domain/error_message.hpp"
// #include "domain/file_reader.hpp"

#include <fstream>

#include "post/journal_handler.hpp"
#include "post/plan_handler.hpp"
#include "server/server.hpp"

#include "generate_code.hpp"
#include "program_state.hpp"

//--------------------------------------------------------------------------------

// data::DBSettings core::Core::mDBS;

core::Core::Core() noexcept
{
    generateDatabaseStructuresFiles();

    mDBS.name     = "journal_db";
    mDBS.user     = "journal_user";
    mDBS.password = "111";
    mDBS.shame    = "journal";

    mAdminDBS.name     = "postgres";
    mAdminDBS.user     = "postgres";
    mAdminDBS.password = "111";
    mAdminDBS.shame    = "public";

    std::ifstream ios("database.pass");
    if (!ios.is_open())
    {
        std::cout << "NO DATABASE PASSWORD FILE DETECTED!\n";
        exit(0);
    }
    ios >> mAdminDBS.password >> mDBS.password;

    mApps["server"] = std::move(std::thread(&Core::serverThread, this));
}

// void
// core::Core::databaseSettingsInit() noexcept
// {
//     mDBS.name     = "journal_db";
//     mDBS.user     = "journal_user";
//     mDBS.password = "111";
//     mDBS.shame    = "journal";

//     std::ifstream ios("database.pass");
//     ios >> mDBS.password >> mDBS.password;
// }

void
core::Core::createJournals() noexcept
{
    data::DatabaseQuery dbq(mDBS);
    post::JournalHandler::loadFromFile("journals.data", dbq);
}

void
core::Core::createPlans() noexcept
{
    data::DatabaseQuery dbq(mDBS);
    post::PlanHandler::parseDataFile("plans.data", dbq);
}

void
core::Core::remakeDatabase()
{
    deleteEnvironment();
    createEnvironment();
    createDatabaseFromFile("database.data");
    populateDatabaseFromFile("populate_basic.data");
}

void
core::Core::populate()
{
    populateDatabaseFromFile("populate_database.data");
    createPlans();
    createJournals();
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

    // for (auto& i : methodMap)
    // {
    //     if (mCommand.getCommand() == i.first) i.second;
    // }

    auto& state = ProgramState::getInstance();

    bool flag = true;
    while (true)
    {
        // std::string s;
        // std::cin >> s;

        // if (s == "create") createDatabaseFromFile("database.data");
        // else if (s == "populate")
        //     populateDatabaseFromFile("populate_database.data");
        // else if (s == "set_up") createEnvironment();
        // else if (s == "remake")
        // {
        //     createDatabaseFromFile("database");
        //     populateDatabaseFromFile("populate_database");
        // }

        if (state.needRestart())
        {
            state.startRestart();
            if (state.needRemakeDB()) remakeDatabase();
            if (state.needPopulateDB()) populate();
            state.endRestart();
        }

        // std::cin >> n;
        // std::cout << n * n << "\n";
        // if (flag)
        // {
        //     mApps["server"] = std::move(std::thread(&Core::serverThread,
        //     this));
        // }

        // flag = false;
    }
}

void
core::Core::serverThread() noexcept
{
    serv::Server app(mDBS);
    while (true)
        ;
}

void
core::Core::createDatabaseFromFile(std::string aFileName) noexcept
{
    data::DatabaseQuery DBQ(mDBS);

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
            if (name.size()) DBQ.createTable(name, colums);
            colums.clear();
            name = s2;
        }
        else
        {
            // colums.emplace_back(data::ColumSetting(s1, s2, ""));
            colums.emplace_back(s1, s2);
        }
    }
}

#include <sstream>

void
core::Core::populateDatabaseFromFile(std::string aFileName) noexcept
{
    data::DatabaseQuery DBQ(mDBS);

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
        std::getline(ios, s2);
        std::getline(ios, s2);
        std::stringstream ss;

        while (s2 != "END")
        {
            std::stringstream ss;
            ss << s2;

            std::vector<std::string> data;
            while (std::getline(ss, s2, ';'))
            {
                if (s2.back() == ';') s2.back() = ' ';
                data.emplace_back(s2);
            }
            DBQ.insert(s1, data);
            std::getline(ios, s2);
        }
    }
}

void
core::Core::createEnvironment() noexcept
{
    data::DatabaseQuery DBQ(mAdminDBS);
    DBQ.createEnvironment(mDBS);
}

void
core::Core::deleteEnvironment() noexcept
{
    data::DatabaseQuery DBQ(mAdminDBS);
    DBQ.dropDatabase(mDBS);
}
