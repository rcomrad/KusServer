#include "command.hpp"

#include "string/parser.hpp"

core::Command::Command(const char* aStr) noexcept
{
    // auto args = str::Parser::slice(aStr, "; \n\t");
    // value     = std::move(args[0]);
    // args.erase(args.begin());

    // for (auto& i : args)
    // {
    //     auto temp = str::Parser::slice(i, "=");
    //     if (temp.size() == 1)
    //     {
    //         arguments.insert(std::move(temp[0]));
    //     }
    //     else
    //     {
    //         variables[std::move(temp[0])] = std::move(temp[1]);
    //     }
    // }
}
