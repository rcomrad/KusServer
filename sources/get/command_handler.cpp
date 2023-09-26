#include "command_handler.hpp"

#include "core/dump_manager.hpp"
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
    int resValue    = 0;
    auto& state     = file::VariableStorage::getInstance();

    if (aValue == "full")
    {
        resValue = 7;
        res      = "OK\nFull restart!";
    }
    else if (aValue == "empty")
    {
        resValue = 1;
        res      = "OK\nEmpty restart!";
    }
    else if (aValue == "tester")
    {
        resValue = 4;
        res      = "OK\nTester restart!";
    }

    if (resValue)
    {
        auto dumpPath = core::DumpManager::dumpAsFile();
        if (dumpPath.has_value())
        {
            res += "\n\nDump address: " + dumpPath.value();
            state.setVariable("restart", resValue);
        }
        else
        {
            res = "ERROR\nCan't create dump!";
        }
    }

    while (state.getIntUnsafe("restart"))
        ;

    return res;
}
