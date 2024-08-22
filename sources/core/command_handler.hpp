#pragma once

//--------------------------------------------------------------------------------

#include <mutex>
#include <queue>

#include "string/kus_string.hpp"

#include "command.hpp"
#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
using CommandFPTR = void (*)(Command& aCommand);

class CommandHandler
{
public:
    HOLY_TRINITY_SINGLETON(CommandHandler);

    SINGL_VOID_METHOD(pushCommand, (Command && aCommand));
    SINGL_VOID_METHOD(handlCommand, ());

    static inline const char CALLBACK_VOLUME_COMMAND_HANDLER[] = "command";

private:
    CommandHandler() noexcept = default;

    std::mutex queue_lock;
    std::queue<Command> mCommandQueue;
};
} // namespace core

//--------------------------------------------------------------------------------
