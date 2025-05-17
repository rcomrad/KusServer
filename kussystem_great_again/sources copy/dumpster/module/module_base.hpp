#ifndef MODULE_BASE_HPP
#define MODULE_BASE_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "file_data/value.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class ModuleBase
{
public:
    struct Command
    {
        int num;
        str::String value;
        str::String argument;

        Command(int a, const char* b, const char* c);
    };
    virtual str::String doAction(const Command& aCommand) noexcept = 0;

protected:
    ModuleBase(const std::vector<str::String>& aNameArray) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !MODULE_BASE_HPP
