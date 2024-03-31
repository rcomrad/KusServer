#include "command.hpp"

#include "text_data/parser.hpp"

route::Command::Command(const str::string& aValue,
                        const str::string& aArguments) noexcept
    : value(aValue)
{
    auto args = text::Parser::slice(aArguments, "; \n\t");
    for (auto& i : args)
    {
        auto temp = text::Parser::slice(i, "=");
        if (temp.size() == 1)
        {
            arguments.insert(std::move(temp[0]));
        }
        else
        {
            variables[temp[0]] = temp[1];
        }
    }
}
