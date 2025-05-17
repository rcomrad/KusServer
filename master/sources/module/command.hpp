#ifndef COMMAND_HPP
#define COMMAND_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace modul
{
struct Command
{
    int num;
    std::string value;
    std::string argument;
    bool saveResult;

    Command(int a, const std::string& b, const std::string& c, bool r) noexcept;
};
} // namespace modul

//--------------------------------------------------------------------------------

#endif // !COMMAND_HPP
