#include "command_handler.hpp"

#include <iostream>

#include "callback_storage.hpp"
#include "logging.hpp"

void
core::CommandHandler::scanCommand() noexcept
{
    while (true)
    {
        str::string inp;
        std::getline(std::cin, inp);
        if (!inp.empty())
        {
            pushCommand(Command(inp));
        }
    }
}

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
        LOG_INFO("Command applyed: ", command.value);
    }
    else
    {
        LOG_ERROR("Command don't applyed: can't call nulptr, command: ",
                  command.value);
    }
}
