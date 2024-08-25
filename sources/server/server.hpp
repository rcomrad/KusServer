#pragma once

//--------------------------------------------------------------------------------

#include "core/holy_trinity.hpp"
#include "core/module.hpp"

//--------------------------------------------------------------------------------

enum ServerVariables
{
    TOKEN_STATUS_VAR
};

namespace serv
{
class Server : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(Server);
    ~Server() override = default;

    void initialize() noexcept override;
    void run() noexcept override;
    void variableSetup(
        core::VariableInfoArray& a_var_set_array) noexcept override;

private:
    Server() noexcept;
    COMMAND_HANDLER_NONSTATIC(tokenCommandHandler);
};

} // namespace serv

//--------------------------------------------------------------------------------
