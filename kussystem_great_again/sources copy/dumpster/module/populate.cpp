#include "populate.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "multitool/dump_manager.hpp"
#include "post/journal_handler.hpp"
#include "post/plan_handler.hpp"
#include "post/user_handler.hpp"

// TODO: to commands
//--------------------------------------------------------------------------------

mod::Populate mod::Populate::mInstance;

mod::Populate::Populate() noexcept : ModuleBase({"restart"})
{
}

//--------------------------------------------------------------------------------

str::String
mod::Populate::doAction(const Command& aCommand) noexcept
{
    int state = 0;
    if (aCommand.argument == "empty") state = 1;
    if (aCommand.argument == "full") state = 3;

    auto dumpPath = mult::DumpManager::makeSaveFile();
    str::String res;
    if (dumpPath.has_value())
    {
        res = "No restart.";
        if (state & 1)
        {
            remakeDatabase();
            res = "OK\nEmpty restart!";
        }
        if (state & 2)
        {
            populate();
            res = "OK\nFull restart!";
        }

        res += "\n\nDump address: " + dumpPath.value();
    }
    else
    {
        res = "ERROR\nCan't create dump!";
    }

    return res;
}

void
mod::Populate::remakeDatabase() noexcept
{
    createEnvironment();
    createDatabaseFromFile(
        core::Path::getPathUnsafe("config", "database.psql_db"));
    post::PostHandler::uploadFromFile(
        {
            {"type", "nun"}
    },
        core::Path::getPathUnsafe("config", "database.dmp"));
}

void
mod::Populate::populate() noexcept
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

    // post::PostHandler::uploadFromFile(
    //     {
    //         {"type",       "plan"                  },
    //         {"name",       "Информатика"},
    //         {"subject_id", "1"                     }
    // },
    //     "../tests/plan_test.csv");
    // post::PostHandler::uploadFromFile(
    //     {
    //         {"type",       "plan"},
    //         {"name",       "C++" },
    //         {"subject_id", "1"   }
    // },
    //     "../tests/plan_cpp.csv");

    // post::PostHandler::uploadFromFile(
    //     {
    //         {"type", "journal_table"}
    // },
    //     "../tests/journal.data");
}

void
mod::Populate::createDatabaseFromFile(str::String aFileName) noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();

    std::vector<data::ColumnSetting> colums;
    auto lines = file::File::getWords(aFileName);
    lines.emplace_back(std::vector<str::String>{"TABLE", "NUN"});
    str::String name;
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
            str::String col;
            for (int j = 1; j < i.size(); ++j) col += i[j] + " ";
            colums.emplace_back(i[0], col);
        }
    }
}

void
mod::Populate::createEnvironment() noexcept
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
