#ifndef COMMAND_HPP
#define COMMAND_HPP

//--------------------------------------------------------------------------------

#include <unordered_map>
#include <unordered_set>

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace route
{
struct Command
{
    str::string value;
    std::unordered_set<str::string> arguments;
    std::unordered_map<str::string, str::string> variables;

    Command(const str::string& aValue, const str::string& aArguments) noexcept;
};
} // namespace route

//--------------------------------------------------------------------------------

#endif // !COMMAND_HPP
