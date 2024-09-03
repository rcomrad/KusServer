#include "register.hpp"

#include "registry.hpp"

void
core::CommandRegister::registerCommand(const char* a_comm_name,
                                       FP_CommandHandler a_func_ptr,
                                       const char* a_help_info,
                                       const char* a_help_args) noexcept
{
    registerCallback(std::string(CALLBACK_VOLUME_COMMAND_HANDLER), a_comm_name,
                     (void*)a_func_ptr);
    CommandHandler::addCommandInfo(a_comm_name, a_help_info, a_help_args);
}

void
core::CommandRegister::registerCommand(
    std::unordered_set<Info>&& a_cmd_data_array) noexcept
{
    for (const auto& i : a_cmd_data_array)
    {
        registerCommand(i.comm_name, i.func_ptr, i.help_info, i.help_args);
    }
}

void
core::CommandRegister::setCommandStateType(
    const char* a_comm_name,
    StateStorage::StateType a_type) noexcept
{
    StateStorage::setStateType(a_comm_name, a_type);
}
