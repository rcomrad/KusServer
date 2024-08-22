#include "command_handler.hpp"

#include <iostream>

#include "callback_storage.hpp"
#include "logging.hpp"

SINGLETON_DEFINITOR(core, CommandHandler);

void
core::CommandHandler::pushCommandNonstatic(Command&& aCommand) noexcept
{
    queue_lock.lock();
    mCommandQueue.push(std::move(aCommand));
    queue_lock.unlock();
}

void
core::CommandHandler::handlCommandNonstatic() noexcept
{
    queue_lock.lock();
    if (mCommandQueue.empty())
    {
        queue_lock.unlock();
        return;
    }
    auto command = std::move(mCommandQueue.front());
    mCommandQueue.pop();
    queue_lock.unlock();

    auto temp =
        CallbackStorage::get(CALLBACK_VOLUME_COMMAND_HANDLER, command.value);
    if (nullptr != temp)
    {
        ((CommandFPTR)temp)(command);
        LOG_INFO("Applyed command: '%s'", command.value);
    }
    else
    {
        COMMAND_RETURN_ERROR(
            command,
            "Unable to apply command '%s'. No suitable command handler",
            command.value);
    }

    command.callOutputFunc();
}
