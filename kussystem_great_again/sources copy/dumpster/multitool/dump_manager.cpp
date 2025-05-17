#include "dump_manager.hpp"

#include "domain/date_and_time.hpp"
#include "domain/log.hpp"

#include "core/variable_storage.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "get/get_router.hpp"
#include "post/post_handler.hpp"

//--------------------------------------------------------------------------------

mult::DumpManager mult::DumpManager::mInstance;

mult::DumpManager::DumpManager() noexcept
    : ModuleBase({"dump", "dump_as_file", "dump_as_html"})
{
}

//--------------------------------------------------------------------------------

str::String
mult::DumpManager::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    // TODO: don't save in file
    str::String file = msg.get_part_by_name("file").body;
    auto path        = file::File::writeData(
        "bin", dom::DateAndTime::getCurentTimeSafe() + ".dmp", file);

    post::PostHandler::uploadFromFile(
        {
            {"type", "nun"}
    },
        path.value());

    return "1";
}

std::optional<str::String>
mult::DumpManager::makeSaveFile() noexcept
{
    std::optional<str::String> result;

    auto flag = !core::VariableStorage::touchFlag("bad_db_flag");
    if (flag)
    {
        result = mult::DumpManager::dumpAsFile();
    }
    else
    {
        result = "NUN";
    }

    return result;
}

str::String
mult::DumpManager::makeDump(const char* aCommand, const char* aArgs) noexcept
{
    return privateProcess(aCommand, aArgs);
}

//--------------------------------------------------------------------------------

str::String
mult::DumpManager::doAction(const Command& aCommand) noexcept
{
    return privateProcess(aCommand.value, aCommand.argument);
}

str::String
mult::DumpManager::privateProcess(const char* aCommand,
                                  const char* aArgs) noexcept
{
    auto processedArgs = file::Parser::slice(aArgs, ",", "*");

    str::String result = "ERROR: wrong dump type!";
    if (aCommand == "dump")
    {
        result = dumpAsString(processedArgs);
    }
    else if (aCommand == "dump_as_file")
    {
        auto path = mult::DumpManager::dumpAsFile(processedArgs);
        if (path.has_value()) result = path.value();
        else result = "Can't create dump!"s;
    }
    else if (aCommand == "dump_as_html")
    {
        // TODO:
        result = dumpAsHTML(processedArgs);
    }

    return result;
}

//--------------------------------------------------------------------------------

str::String
mult::DumpManager::dumpAsString(
    const std::vector<str::String>& aTableNames) noexcept
{
    static std::vector<str::String> databaseTables = getDatabaseTableNames();
    const std::vector<str::String>& names =
        aTableNames.empty() ? databaseTables : aTableNames;

    str::String result;

    for (auto& i : names)
    {
        result += get::GetRouter::dumpRouter(i);
        result.push_back('\n');
    }

    return result;
}

std::optional<str::String>
mult::DumpManager::dumpAsFile(
    const std::vector<str::String>& aTableNames) noexcept
{
    auto data = dumpAsString(aTableNames);
    auto path = file::File::writeData(
        "dump", dom::DateAndTime::getCurentTimeSafe() + ".dmp", data);

    if (!path.has_value()) LOG_ERROR("Can't create file in dump folder");
    return path;
}

str::String
mult::DumpManager::dumpAsHTML(
    const std::vector<str::String>& aTableNames) noexcept
{
    auto data = dumpAsString(aTableNames);

    str::String res;
    for (auto i : data)
    {
        res += i;
        if (i == '\n') res += "<br>";
    }
    return res;
}

//--------------------------------------------------------------------------------

std::vector<str::String>
mult::DumpManager::getDatabaseTableNames() noexcept
{
    std::vector<str::String> result;

    auto words = file::File::getWords("config"s, "database.psql_db"s);
    for (auto& i : words)
    {
        if (i[0] == "TABLE") result.emplace_back(std::move(i[1]));
    }

    return result;
}
