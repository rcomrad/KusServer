#include "command_reader.hpp"

#include <iostream>
#include <string>

#include "core.hpp"

#include "command_handler.hpp"
#include "yield.hpp"

TRIGGER_SINGLETON_ENTRY_POINT(core::CommandReader);

core::CommandReader::CommandReader() noexcept : Module("command_reader")
{
}

void
core::CommandReader::run() noexcept
{
    std::string inp;
    while (Core::isRunning())
    {
        std::getline(std::cin, inp);
        CommandHandler::pushCommand(inp);

        // TODO: do we even need yield?
        Yield::large();
    }
}
