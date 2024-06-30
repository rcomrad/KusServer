#pragma once

//--------------------------------------------------------------------------------

#include <mutex>
#include <queue>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"

#include "command.hpp"

//--------------------------------------------------------------------------------

namespace core
{
using CommandFPTR = void (*)(const Command& aCommand);

class CommandHandler
{
public:
    HOLY_TRINITY_SINGLETON(CommandHandler);

    static void scanCommand() noexcept;

    SINGL_VOID_METHOD(pushCommand, (Command && aCommand));
    SINGL_VOID_METHOD(handlCommand, ());

    static inline const char CALLBACK_VOLUME_COMMAND_HANDLER[] = "command";

private:
    CommandHandler() noexcept = default;

    std::mutex queue_lock;
    std::queue<Command> mCommandQueue;
};
} // namespace core

#define COMMAND_METHOD_STATIC(name) \
    static void name(const Command& aCommand) noexept;
#define COMMAND_METHOD_NONSTATIC(name) \
    SINGL_PRIV_VOID_METHOD(name, (const Command& aCommand))

//--------------------------------------------------------------------------------
