#include "command.hpp"

#include "kus_standard/parser.hpp"

core::Command::Command() noexcept : ready(false)
{
    buffer[0] = 0;
}

// TODO: do we nedd move?
void
core::Command::assemble() noexcept
{
    auto args = kstd::Parser::slice(buffer, "; \n\t");
    value     = std::move(args[0]);

    for (int i = 1; i < args.size(); ++i)
    {
        auto temp = kstd::Parser::slice(args[i], "=");
        if (temp.size() == 1)
        {
            arguments.insert(std::move(temp[0]));
        }
        else
        {
            variables[std::move(temp[0])] = std::move(temp[1]);
        }
    }

    ready = true;
}
