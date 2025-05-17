#include "dump_manager.hpp"

#include "domain/date_time.hpp"
#include "domain/time_handler.hpp"
#include "domain/variable_storage.hpp"

#include "text_data/file.hpp"
#include "text_data/parser.hpp"

#include "get/get_router.hpp"

#include "post/post_handler.hpp"

#include "general_tools/log.hpp"

//--------------------------------------------------------------------------------

mult::DumpManager mult::DumpManager::mInstance;

mult::DumpManager::DumpManager() noexcept
    : ModuleBase({"dump", "dump_as_file", "dump_as_html"})
{
}

//--------------------------------------------------------------------------------

std::string
mult::DumpManager::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    // TODO: don't save in file
    std::string file = msg.get_part_by_name("file").body;
    auto path        = text::File::writeData(
        "bin", dom::TimeHandler::getCurentTime().getAllNoSpace() + ".dmp",
        file);

    post::PostHandler::uploadFromFile(
        {
            {"type", "nun"}
    },
        path.value());

    return "1";
}

std::optional<std::string>
mult::DumpManager::makeSaveFile() noexcept
{
    std::optional<std::string> result;

    auto flag = !dom::VariableStorage::touchFlag("bad_db_flag");
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

std::string
mult::DumpManager::makeDump(const std::string& aCommand,
                            const std::string& aArgs) noexcept
{
    return privateProcess(aCommand, aArgs);
}

//--------------------------------------------------------------------------------

std::string
mult::DumpManager::doAction(const Command& aCommand) noexcept
{
    return privateProcess(aCommand.value, aCommand.argument);
}

std::string
mult::DumpManager::privateProcess(const std::string& aCommand,
                                  const std::string& aArgs) noexcept
{
    auto processedArgs = text::Parser::slice(aArgs, ",", "*");

    std::string result = "LOG_ERROR: wrong dump type!";
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

std::string
mult::DumpManager::dumpAsString(
    const std::vector<std::string>& aTableNames) noexcept
{
    static std::vector<std::string> databaseTables = getDatabaseTableNames();
    const std::vector<std::string>& names =
        aTableNames.empty() ? databaseTables : aTableNames;

    std::string result;

    for (auto& i : names)
    {
        result += get::GetRouter::dumpRouter(i);
        result.push_back('\n');
    }

    return result;
}

std::optional<std::string>
mult::DumpManager::dumpAsFile(
    const std::vector<std::string>& aTableNames) noexcept
{
    auto data = dumpAsString(aTableNames);
    auto path = text::File::writeData(
        "dump", dom::TimeHandler::getCurentTime().getAllNoSpace() + ".dmp",
        data);

    if (!path.has_value()) LOG_ERROR("Can't create file in dump folder");
    return path;
}

std::string
mult::DumpManager::dumpAsHTML(
    const std::vector<std::string>& aTableNames) noexcept
{
    auto data = dumpAsString(aTableNames);

    std::string res;
    for (auto i : data)
    {
        res += i;
        if (i == '\n') res += "<br>";
    }
    return res;
}

//--------------------------------------------------------------------------------

std::vector<std::string>
mult::DumpManager::getDatabaseTableNames() noexcept
{
    std::vector<std::string> result;

    auto words = text::File::getWords("config"s, "database.psql_db"s);
    for (auto& i : words)
    {
        if (i[0] == "TABLE") result.emplace_back(std::move(i[1]));
    }

    return result;
}
