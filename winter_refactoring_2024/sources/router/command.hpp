#ifndef COMMAND_HPP
#define COMMAND_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//--------------------------------------------------------------------------------

namespace route
{
struct Command
{
    std::string value;
    std::unordered_set<std::string> arguments;
    std::unordered_map<std::string, std::string> variables;

    Command(const std::string& aValue, const std::string& aArguments) noexcept;
};
} // namespace base

//--------------------------------------------------------------------------------

#endif // !COMMAND_HPP
