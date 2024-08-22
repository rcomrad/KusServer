#include "command_reader.hpp"

#include <iostream>
#include <string>

#include "core.hpp"

#include "command_handler.hpp"
#include "yield.hpp"

SINGLETON_DEFINITOR(core, CommandReader);

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
        CommandHandler::pushCommand(Command{inp, stdoutOutput});

        // TODO: do we even need yield?
        Yield::large();
    }
}

void
core::CommandReader::stdoutOutput(const char* a_buff) noexcept
{
    if (a_buff == nullptr)
    {
        LOG_ERROR("Empty command result buffer");
        return;
    }
    fprintf(stdout, "%s", a_buff);
    fflush(stdout);
}
