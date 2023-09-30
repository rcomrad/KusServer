#include "core.hpp"

#include <fstream>

#include "database/connection_manager.hpp"

#include "code/generate_code.hpp"
#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "file_data/variable_storage.hpp"
#include "get/command_handler.hpp"
#include "post/journal_handler.hpp"
#include "post/plan_handler.hpp"
#include "post/user_handler.hpp"
#include "tester/tester.hpp"

#include "server.hpp"
#include "submission_queue.hpp"

//--------------------------------------------------------------------------------

void
loadQuestions()
{
    auto connection = data::ConnectionManager::getUserConnection();
    // connection.val.drop("question", "id > 0");

    auto hasQ = file::Path::getContentMap(file::Path::getPathUnsafe("question"),
                                          file::Path::FileType::Folder);
    std::map<std::string, std::string> q;
    q.insert(hasQ.begin(), hasQ.end());

    auto ans = file::File::getWordsMap("question"s, "ans.txt"s);

    for (auto& i : q)
    {
        data::Question q = connection.val.getData<data::Question>(
            "nickname=\'" + i.first + "\'");

        q.name       = i.first;
        q.nickname   = i.first;
        q.type       = 1;
        q.weight     = 1;
        q.juryAnswer = "1";

        auto it = ans.find(i.first);
        if (it != ans.end())
        {
            q.juryAnswer = it->second;
        }

        connection.val.write(q);
    }
}

core::Core::Core() noexcept
{
    code::CodeGenerator cg;
    cg.makeAll();
    cg.generate();

    mApps["server"] = std::move(std::thread(&Core::serverThread, this));
    if (file::VariableStorage::getInstance().getFlagUnsafe(
            "submission_auto_check"))
        mApps["tester"] = std::move(std::thread(&Core::testerThread, this));

    if (!file::VariableStorage::getInstance().getFlagUnsafe("bad_db_flag"))
    {
        loadQuestions();
    }

    auto restartState =
        file::VariableStorage::getInstance().getWord("restart_on_start");
    if (restartState.has_value())
    {
        mApps["database_remake"] =  
            std::move(std::thread(&get::CommandHandler::process,"restart", restartState.value()));
    }
}

void
core::Core::remakeDatabase()
{
    createEnvironment();
    createDatabaseFromFile(
        file::Path::getPathUnsafe("config", "database.psql_db"));
    post::PostHandler::uploadFromFile(
        {
            {"type", "nun"}
    },
        file::Path::getPathUnsafe("config", "database.dmp"));
}

void
core::Core::populate()
{
    post::PostHandler::uploadFromFile(
        {
            {"type", "nun"}
    },
        "../tests/example.dmp");

    post::PostHandler::uploadFromFile(
        {
            {"type", "user"}
    },
        "../tests/user.data");

    post::PostHandler::uploadFromFile(
        {
            {"type",       "plan"                  },
            {"name",       "Информатике"},
            {"subject_id", "1"                     }
    },
        "../tests/plan_test.csv");
    post::PostHandler::uploadFromFile(
        {
            {"type",       "plan"},
            {"name",       "C++" },
            {"subject_id", "1"   }
    },
        "../tests/plan_cpp.csv");

    post::PostHandler::uploadFromFile(
        {
            {"type", "journal_table"}
    },
        "../tests/journal.data");
}

void
core::Core::run() noexcept
{
    auto& state = file::VariableStorage::getInstance();

    file::Path::addContentFrom(file::Path::getPathUnsafe("resource"),
                               file::Path::FileType::File,
                               file::Path::LevelType::Recursive);
    file::Path::addContentFrom(file::Path::getPathUnsafe("scripts"));

    // TODO: optional
    bool flag = true;
    while (true)
    {
        auto num = state.getIntUnsafe("restart");
        if (num)
        {
            if (num & 1) 
            {
                remakeDatabase();
            }
            if (num & 2) 
            {
                populate();
            }
            if (num & 4)
            {
                SubmissionQueue::getInstance().reload();
            }

            state.setVariable("restart", 0);
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
    auto& sub = SubmissionQueue::getInstance();
    while (true)
    {

        if (!sub.isEmpty())
        {
            dom::writeInfo("start_checking");
            test::Tester tester(
                file::VariableStorage::getInstance().getIntUnsafe(
                    "tester_thread_count"));
            tester.run(sub.get());
            dom::writeInfo("end_checking");
        }
    }
}

void
core::Core::createDatabaseFromFile(std::string aFileName) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();

    std::vector<data::ColumnSetting> colums;
    auto lines = file::File::getWords(aFileName);
    lines.emplace_back(std::vector<std::string>{"TABLE", "NUN"});
    std::string name;
    for (auto i : lines)
    {
        if (i[0] == "TABLE")
        {
            if (!name.empty()) connection.val.createTable(name, colums);
            colums.clear();
            name = i[1];
        }
        else
        {
            // TODO: beter
            std::string col;
            for (int j = 1; j < i.size(); ++j) col += i[j] + " ";
            colums.emplace_back(i[0], col);
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
