#include "command_handler.hpp"

#include "core/program_state.hpp"

std::string
get::CommandHandler::process(const std::string& aType,
                             const std::string& aValue) noexcept
{
    std::string res = "ERROR\nInvalid command!\n>:(\n";

    auto& state = core::ProgramState::getInstance();

    // std::cout << "======= \'" << aType << "\'\n";

    if (aType == "restart")
    {
        res = "ERROR\nNo restart :( \nInvalid restart value.";

        if (aValue == "full")
        {
            state.fullReset();
            res = "OK\nFull restart!";
        }
        else if (aValue == "empty")
        {
            state.emptyReset();
            res = "OK\nEmpty restart!";
        }
        else if (aValue == "tester")
        {
            state.testerReset();
            res = "OK\nTester restart!";
        }
    }
    else if (aType == "check")
    {
        res = "ERROR\nInvalid value!";
        if (aValue == "on")
        {
            state.setCheckAnswers(core::ProgramState::State::ON);
            res = "ERROR\nChecking turned on!";
        }
        else if (aValue == "off")
        {
            state.setCheckAnswers(core::ProgramState::State::OFF);
            res = "ERROR\nChecking turned off!";
        }
    }
    else if (aType == "time")
    {
        res = "ERROR\nInvalid value!";
        if (aValue == "on")

        {
            state.setSettingTime(core::ProgramState::State::ON);
            res = "ERROR\nSetting time turned on!";
        }
        else if (aValue == "off")
        {
            state.setSettingTime(core::ProgramState::State::OFF);
            res = "ERROR\nSetting time turned off!";
        }
    }

    return res;
}
