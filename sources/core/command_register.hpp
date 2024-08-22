#pragma once

//--------------------------------------------------------------------------------

#include <vector>

#include "command_handler.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CommandRegister
{
public:
    CommandRegister() noexcept = default;

protected:
    struct CommandData
    {
        const char* comm_name;
        CommandFPTR func_ptr;

        // inline CommandData(const char* a_comm_name, CommandFPTR a_func_ptr)
        //     : comm_name(a_comm_name), func_ptr(a_func_ptr)
        // {
        // }
    };
    using CommandDataArray = std::vector<CommandData>;

    void registerCommand(const char* a_comm_name,
                         CommandFPTR a_func_ptr) noexcept;
    // void registerCommand(const CommandData& a_command_data) noexcept;
    // void registerCommand(const CommandDataArray& a_command_data) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
