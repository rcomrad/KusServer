#include "command_handler.hpp"

#include "database/connection_manager.hpp"

#include "core/program_state.hpp"

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
    auto& state     = core::ProgramState::getInstance();

    if (aValue == "full")
    {
        state.callRestart(core::RestartType::FULL);
        res = "OK\nFull restart!";
    }
    else if (aValue == "empty")
    {
        state.callRestart(core::RestartType::EMPTY);
        res = "OK\nEmpty restart!";
    }
    else if (aValue == "tester")
    {
        state.callRestart(core::RestartType::TESTER);
        res = "OK\nTester restart!";
    }
    else if (aValue == "settings")
    {
        state.callRestart(core::RestartType::SETTINGS);
        res = "OK\nTester restart!";
    }

    return res;
}

// std::string
// get::CommandHandler::check(const std::string aValue) noexcept
// {
//     std::string res = "ERROR\nInvalid value!";
//     auto& state     = core::ProgramState::getInstance();

//     if (aValue == "on")
//     {
//         state.setCheckAnswers(core::ProgramState::State::ON);
//         res = "ERROR\nChecking turned on!";
//     }
//     else if (aValue == "off")
//     {
//         state.setCheckAnswers(core::ProgramState::State::OFF);
//         res = "ERROR\nChecking turned off!";
//     }
//     return res;
// }

// std::string
// get::CommandHandler::time(const std::string aValue) noexcept
// {
//     std::string res = "ERROR\nInvalid value!";
//     auto& state     = core::ProgramState::getInstance();

//     if (aValue == "on")

//     {
//         state.setSettingTime(core::ProgramState::State::ON);
//         res = "ERROR\nSetting time turned on!";
//     }
//     else if (aValue == "off")
//     {
//         state.setSettingTime(core::ProgramState::State::OFF);
//         res = "ERROR\nSetting time turned off!";
//     }
// }

std::string
get::CommandHandler::dump(const std::string aValue) noexcept
{
    // TODO: block database

    std::string res = "ERROR\nNo restart :( \nInvalid restart value.";
    auto& state     = core::ProgramState::getInstance();

    if (aValue == "full")
    {
        state.callRestart(core::RestartType::FULL);
        res = "OK\nFull restart!";
    }
    else if (aValue == "empty")
    {
        state.callRestart(core::RestartType::EMPTY);
        res = "OK\nEmpty restart!";
    }
    else if (aValue == "tester")
    {
        state.callRestart(core::RestartType::TESTER);
        res = "OK\nTester restart!";
    }
    else if (aValue == "settings")
    {
        state.callRestart(core::RestartType::SETTINGS);
        res = "OK\nTester restart!";
    }

    return res;
}
