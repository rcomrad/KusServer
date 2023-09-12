#include "command_handler.hpp"

#include "domain/date_and_time.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "file_data/variable_storage.hpp"
#include "get/get_router.hpp"

std::unordered_map<std::string, decltype(&get::CommandHandler::restart)>
    get::CommandHandler::mRouterMap = {
        {"restart", &get::CommandHandler::restart},
 // {"check",   &get::CommandHandler::check  },
  // {"time",    &get::CommandHandler::time   }
};

std::string
get::CommandHandler::process(const std::string& aType,
                             const std::string& aValue) noexcept
{
    std::string res = "ERROR\nInvalid command!\n>:(\n";
    auto it         = mRouterMap.find(aType);
    if (it != mRouterMap.end()) res = it->second(aValue);
    return res;
}

std::vector<std::string>
foo()
{
    auto words = file::File::getWords(
        file::Path::getPathUnsafe("config", "database.psql_db"));

    std::vector<std::string> result;
    for (auto& i : words)
    {
        if (i[0] == "TABLE") result.emplace_back(std::move(i[1]));
    }

    return result;
}

std::string
get::CommandHandler::restart(const std::string aValue) noexcept
{
    static std::vector<std::string> allTableNames = foo();
    std::string dump;
    for (auto& i : allTableNames)
    {
        dump += get::GetRouter::dumpRouter(i, false);
    }
    file::File::writeData("dump",
                          dom::DateAndTime::getCurentTimeSafe() + ".dmp", dump);

    std::string res = "ERROR\nNo restart :( \nInvalid restart value.";
    auto& state     = file::VariableStorage::getInstance();

    if (aValue == "full")
    {
        state.setVariable("restart", 7);
        res = "OK\nFull restart!";
    }
    else if (aValue == "empty")
    {
        state.setVariable("restart", 1);
        res = "OK\nEmpty restart!";
    }
    else if (aValue == "tester")
    {
        state.setVariable("restart", 4);
        res = "OK\nTester restart!";
    }

    return res;
}
