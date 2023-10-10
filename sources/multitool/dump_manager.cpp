#include "dump_manager.hpp"

#include "domain/date_and_time.hpp"
#include "domain/log.hpp"

#include "file_data/file.hpp"
#include "file_data/variable_storage.hpp"
#include "get/get_router.hpp"
#include "post/post_handler.hpp"

std::string
mult::DumpManager::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    // TODO: don't save in file
    std::string file = msg.get_part_by_name("file").body;
    auto path        = file::File::writeData(
        "bin", dom::DateAndTime::getCurentTimeSafe() + ".dmp", file);

    post::PostHandler::uploadFromFile(
        {
            {"type", "nun"}
    },
        path.value());

    return "1";
}

std::optional<std::string>
mult::DumpManager::dumpAsFile(
    const std::vector<std::string>& aTableNames) noexcept
{
    auto data = dumpAsString(aTableNames);
    auto path = file::File::writeData(
        "dump", dom::DateAndTime::getCurentTimeSafe() + ".dmp", data);

    if (!path.has_value()) dom::writeError("Can't create file in dump folder");
    return path;
}

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

std::vector<std::string>
mult::DumpManager::getDatabaseTableNames() noexcept
{
    std::vector<std::string> result;

    auto words = file::File::getWords("config"s, "database.psql_db"s);
    for (auto& i : words)
    {
        if (i[0] == "TABLE") result.emplace_back(std::move(i[1]));
    }

    return result;
}

std::optional<std::string>
mult::DumpManager::makeSaveFile() noexcept
{
    std::optional<std::string> result;

    auto flag = file::VariableStorage::getInstance().getFlag("bad_db_flag");
    if (flag.has_value() && !flag.value())
    {
        result = mult::DumpManager::dumpAsFile();
    }
    else
    {
        result = "NUN";
    }

    return result;
}
