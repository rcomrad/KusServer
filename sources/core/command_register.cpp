#include "command_register.hpp"

#include "callback_storage.hpp"

void
core::CommandRegister::registerCommand(const char* a_comm_name,
                                       CommandFPTR a_func_ptr) noexcept
{

    CallbackStorage::add(CommandHandler::CALLBACK_VOLUME_COMMAND_HANDLER,
                         a_comm_name, (void*)a_func_ptr);
}

// void
// core::CommandRegister::registerCommand(
//     const CommandData& a_command_data) noexcept
// {

//     registerCommand(a_command_data.comm_name, a_command_data.func_ptr);
// }

// void
// core::CommandRegister::registerCommand(
//     const CommandDataArray& a_command_data) noexcept
// {
//     for (const auto& i : a_command_data)
//     {
//         registerCommand(i);
//     }
// }
