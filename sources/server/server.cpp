#include "server.hpp"

#include "core/core.hpp"
#include "core/yield.hpp"

#include "token.hpp"

SINGLETON_DEFINITOR(serv, Server)

serv::Server::Server() noexcept : core::Module("server")
{
}

void serv::Server::initialize() noexcept
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
    a_set_array.emplace_back("token_state", serv::Token::getTokenStatus);
}

void
serv::Server::tokenCommandHandlerNonstatic(
        core::Command& aCommand) noexcept
{
    core::Command comm("set token_state=" + *aCommand.arguments.begin(), {});
    core::CommandHandler::pushCommand(std::move(comm));
    COMMAND_RETURN_MSG(aCommand, "Token state changed");
}
