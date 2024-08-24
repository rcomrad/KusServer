#include "server.hpp"

#include <unordered_set>

#include "core/core.hpp"
#include "core/yield.hpp"

#include "token.hpp"

SINGLETON_DEFINITOR(serv, Server)

serv::Server::Server() noexcept : core::Module("server")
{
    registerCommand("token", tokenCommandHandler);
}

void
serv::Server::run() noexcept
{
    while (core::Core::isRunning())
    {
        // TODO: do we need small yeild? maybe "instante"
        core::Yield::small();
    }
}

void
serv::Server::variableSetup(core::VariableInfoArray& a_set_array) noexcept
{
    core::VariableInfo varInfo = {"token_state", &serv::Token::getTokenStatus};
    a_set_array.emplace_back(varInfo);
}

void
serv::Server::tokenCommandHandlerNonstatic(
        core::Command& aCommand) noexcept
{
    if (aCommand.arguments.size() != 1)
    {
        COMMAND_RETURN_ERROR(aCommand, "Can't parse token arguments. Usage: \"token "
                                       "turn_off/turn_on/memory/print\" ");
        return;
    }

    str::string state_val = str::string(*aCommand.arguments.begin());
    std::unordered_set<str::string> token_states = {"turn_off", "turn_on", "memory", "print"};

    if (token_states.find(state_val) == token_states.end())
    {
        COMMAND_RETURN_ERROR(aCommand, "Incorrect token state value: '%s'", state_val);
    }
    else {
        core::Command command = core::Command(
                "set token_state=" + state_val, {});
        COMMAND_RETURN_MSG(aCommand, "Successfully assigned value '%s' to variable: token_state", state_val);
    }
}
