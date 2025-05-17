#include "server.hpp"

#include <iostream>

#include "server_module.hpp"
#include "server_variable.hpp"

serv::Server::Server() noexcept
{
}

serv::Server&
serv::Server::getInstace() noexcept
{
    static Server instance;
    return instance;
}

void
serv::Server::start() noexcept
{
    int var = -1;
    while (var)
    {
        int old_val = var;
        var = ServerModule::getVatiable(ServerVariables::TOKEN_STATUS_VAR);
        if (var != old_val)
        {
            std::cout << var << std::endl;
        }
    }
}
