#include "command_handler.hpp"

#include "database/connection_manager.hpp"

#include "file_data/variable_storage.hpp"

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

std::string
get::CommandHandler::restart(const std::string aValue) noexcept
{
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
