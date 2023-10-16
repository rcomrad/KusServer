#include "populate.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "multitool/dump_manager.hpp"
#include "post/journal_handler.hpp"
#include "post/plan_handler.hpp"
#include "post/user_handler.hpp"

#include "variable_storage.hpp"

// TODO: to commands
//--------------------------------------------------------------------------------

core::Populate core::Populate::mInstance;

core::Populate ::Populate() noexcept
    : ModuleBase("clear", file::Value::Type::String)
{
}

//--------------------------------------------------------------------------------

std::string
core::Populate::doAction() noexcept
{
    static auto& command = VariableStorage::touchWord("clear");

    int state = 0;
    if (command == "empty") state = 1;
    if (command == "full") state = 3;

    auto dumpPath = mult::DumpManager::makeSaveFile();
    std::string res;
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
core::Populate::remakeDatabase() noexcept
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
core::Populate::populate() noexcept
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
            {"name",       "Информатика"},
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
core::Populate::createDatabaseFromFile(std::string aFileName) noexcept
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
core::Populate::createEnvironment() noexcept
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
