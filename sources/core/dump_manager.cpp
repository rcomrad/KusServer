#include "dump_manager.hpp"

#include "domain/date_and_time.hpp"
#include "domain/log.hpp"

#include "file_data/file.hpp"
#include "file_data/variable_storage.hpp"
#include "get/get_router.hpp"

std::optional<std::string>
core::DumpManager::dumpAsFile(
    const std::vector<std::string>& aTableNames) noexcept
{
    auto data = dumpAsString(aTableNames);
    auto path = file::File::writeData(
        "dump", dom::DateAndTime::getCurentTimeSafe() + ".dmp", data);

    if (!path.has_value()) dom::writeError("Can't create file in dump folder");
    return path;
}

std::string
core::DumpManager::dumpAsString(
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
core::DumpManager::getDatabaseTableNames() noexcept
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
core::DumpManager::makeSaveFile() noexcept
{
    std::optional<std::string> result;

    if (!file::VariableStorage::getInstance().getFlag("bad_db_flag"))
    {
        result = core::DumpManager::dumpAsFile();
    }

    return result;
}
