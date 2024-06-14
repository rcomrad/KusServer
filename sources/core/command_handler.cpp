#include "command_handler.hpp"

#include <iostream>

#include "callback_storage.hpp"
#include "logging.hpp"

//--------------------------------------------------------------------------------

void
core::CommandHandler::scanCommand() noexcept
{
    while (true)
    {
        str::String inp;
        std::getline(std::cin, inp);
        if (!inp.empty())
        {
            pushCommand(Command(inp));
        }
    }
}

//--------------------------------------------------------------------------------

core::CommandHandler::CommandHandler() noexcept
{
}

core::CommandHandler&
core::CommandHandler::getInstance() noexcept
{
    static CommandHandler instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
core::CommandHandler::pushCommand(Command&& aCommand) noexcept
{
    getInstance().pushCommandNonstatic(std::move(aCommand));
}

void
core::CommandHandler::pushCommandNonstatic(Command&& aCommand) noexcept
{
    queue_lock.lock();
    mCommandQueue.push(std::move(aCommand));
    queue_lock.unlock();
}

//--------------------------------------------------------------------------------

void
core::CommandHandler::handlCommand() noexcept
{
    getInstance().handlCommandNonstatic();
}

void
core::CommandHandler::handlCommandNonstatic() noexcept
{
    static auto& command_map =
        CallbackStorage::getVolumeCallbacks(CALLBACK_VOLUME_COMMAND_HANDLER);

    queue_lock.lock();
    if (mCommandQueue.empty() || !mCommandQueue.front().ready)
    {
        queue_lock.unlock();
        return;
    }
    Command& command = mCommandQueue.front();
    queue_lock.unlock();

    auto comm_it = command_map.find(command.value);
    if (command_map == command_map.end())
    {
        ((void (*)(const Command&))comm_it->second)(command);
        LOG_INFO("Command applyed: ", command.value);
    }
    else
    {
        LOG_ERROR("Command don't applyed: can't call nulptr, command: ",
                  command.value);
    }

    queue_lock.lock();
    mCommandQueue.pop();
    queue_lock.unlock();
}
