// #pragma once

// //--------------------------------------------------------------------------------

// #include <mutex>
// #include <queue>

// #include "string/kus_string.hpp"

// #include "command.hpp"
// #include "holy_trinity.hpp"

// //--------------------------------------------------------------------------------

// namespace core
// {
// class CommandHandler
// {
// public:
//     HOLY_TRINITY_SINGLE(CommandHandler);
//     static void scanCommand() noexcept;
//     static void pushCommand(Command&& aCommand) noexcept;
//     static void handlCommand() noexcept;

//     static const str::String CALLBACK_VOLUME_COMMAND_HANDLER;

// private:
//     CommandHandler() noexcept;
//     static CommandHandler& getInstance() noexcept;

//     void pushCommandNonstatic(Command&& aCommand) noexcept;
//     void handlCommandNonstatic() noexcept;

//     std::mutex queue_lock;
//     std::queue<Command> mCommandQueue;
// };
// } // namespace core

// //--------------------------------------------------------------------------------
