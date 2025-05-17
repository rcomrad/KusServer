#include "server.hpp"

#include "utility/common/yield.hpp"

#include "token.hpp"

SINGLETON_DEFINITOR(serv, Server)

serv::Server::Server() noexcept : core::Module("server")
{
}

bool
serv::Server::loopBody() noexcept
{
    // TODO: do we need small yeild? maybe "instante"
    util::Yield::small();
    return true;
}

void
serv::Server::commandSetup() const noexcept
{
    registerCommand("token", Token::tokenCommandHandler,
                    "Sets token handling status.", "");
}

void
serv::Server::variableSetup() const noexcept
{
    registerVariable("token_status", serv::Token::VariableStrValues,
                     int(serv::Token::Status::MAX) - 1);
}
