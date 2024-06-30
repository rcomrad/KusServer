#include "command_register.hpp"

#include "callback_storage.hpp"

void
core::CommandRegister::registerCommand(const char* a_comm_name,
                                       CommandFPTR a_func_ptr) noexcept
{

    CallbackStorage::add(CommandHandler::CALLBACK_VOLUME_COMMAND_HANDLER,
                         a_comm_name, (void*)a_func_ptr);
}
