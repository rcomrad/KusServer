#include "command.hpp"

#include "string/parser.hpp"

core::Command::Command(const str::string& aStr) noexcept
{
    auto args = str::Parser::slice(aStr, "; \n\t");
    value     = args[0];
    args.erase(args.begin());

    for (auto& i : args)
    {
        auto temp = str::Parser::slice(i, "=");
        if (temp.size() == 1)
        {
            arguments.insert(str::string(temp[0]));
        }
        else
        {
            variables[str::string(temp[0])] = temp[1];
        }
    }
}
