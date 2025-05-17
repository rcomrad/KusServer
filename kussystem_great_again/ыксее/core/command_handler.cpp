// #include "command_handler.hpp"

// #include <iostream>

// #include "callback_storage.hpp"
// #include "logging.hpp"

// //--------------------------------------------------------------------------------

// const str::String core::CommandHandler::CALLBACK_VOLUME_COMMAND_HANDLER =
//     "command";

// //--------------------------------------------------------------------------------

// void
// core::CommandHandler::scanCommand() noexcept
// {
//     while (true)
//     {
//         str::String inp;
//         std::getline(std::cin, inp);
//         if (!inp.empty())
//         {
//             pushCommand(Command(inp));
//         }
//     }
// }

// //--------------------------------------------------------------------------------

// core::CommandHandler::CommandHandler() noexcept
// {
// }

// core::CommandHandler&
// core::CommandHandler::getInstance() noexcept
// {
//     static CommandHandler instance;
//     return instance;
// }

// //--------------------------------------------------------------------------------

// void
// core::CommandHandler::pushCommand(Command&& aCommand) noexcept
// {
//     getInstance().pushCommandNonstatic(std::move(aCommand));
// }

// void
// core::CommandHandler::pushCommandNonstatic(Command&& aCommand) noexcept
// {
//     queue_lock.lock();
//     mCommandQueue.push(std::move(aCommand));
//     queue_lock.unlock();
// }

// //--------------------------------------------------------------------------------

// void
// core::CommandHandler::handlCommand() noexcept
// {
//     getInstance().handlCommandNonstatic();
// }

// void
// core::CommandHandler::handlCommandNonstatic() noexcept
// {
//     queue_lock.lock();
//     if (mCommandQueue.empty())
//     {
//         queue_lock.unlock();
//         return;
//     }
//     auto command = std::move(mCommandQueue.front());
//     mCommandQueue.pop();
//     queue_lock.unlock();

//     auto temp =
//         CallbackStorage::get(CALLBACK_VOLUME_COMMAND_HANDLER, command.value);
//     if (nullptr != temp)
//     {
//         ((void (*)(const Command& aCommand))temp)(command);
//         LOG_INFO("Command applyed: ", command.value);
//     }
//     else
//     {
//         LOG_ERROR("Command don't applyed: can't call nulptr, command: ",
//                   command.value);
//     }
// }
