#pragma once

//--------------------------------------------------------------------------------

#include <unordered_set>

#include "core/callback/register.hpp"
#include "core/module/state_storage.hpp"

#include "command_extend.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CommandRegister : private CallbackRegister
{
protected:
    struct Info
    {
        const char* comm_name;
        FP_CommandHandler func_ptr;
        const char* help_info;
        const char* help_args = "";
    };
    using CommandInfoArray = std::unordered_set<core::CommandRegister::Info>;

    static void registerCommand(const char* a_comm_name,
                                FP_CommandHandler a_func_ptr,
                                const char* a_help_info,
                                const char* a_help_args = "") noexcept;
    static void registerCommand(
        std::unordered_set<Info>&& a_cmd_data_array) noexcept;
    static void setCommandStateType(const char* a_comm_name,
                                    StateStorage::StateType a_type) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
