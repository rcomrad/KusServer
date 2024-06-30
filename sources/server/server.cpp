#include "server.hpp"

#include <iostream>

#include "core/core.hpp"
#include "core/yield.hpp"

#include "token.hpp"

TRIGGER_SINGLETON_ENTRY_POINT(serv::Server)

serv::Server::Server() noexcept : core::Module("server")
{
}

void
serv::Server::run() noexcept
{
    int var = -1;
    while (core::Core::isRunning())
    {
        int old_val = var;
        var         = getVatiable(ServerVariables::TOKEN_STATUS_VAR);
        if (var != old_val)
        {
            std::cout << var << std::endl;
        }

        // TODO: do we need small yeild? maybe "instante"
        core::Yield::small();
    }
}

void
serv::Server::variableSetup(core::VariableInfoArray& a_set_array) noexcept
{
    a_set_array.emplace_back("token_state", serv::Token::getTokenStatus);
}
