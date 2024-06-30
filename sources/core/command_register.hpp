#pragma once

//--------------------------------------------------------------------------------

#include "command_handler.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CommandRegister
{
public:
    CommandRegister() noexcept = default;

protected:
    void registerCommand(const char* a_comm_name,
                         CommandFPTR a_func_ptr) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
