#ifndef MODULE_BASE_HPP
#define MODULE_BASE_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "text_data/value.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class ModuleBase
{
public:
    struct Command
    {
        int num;
        std::string value;
        std::string argument;
        bool saveResult;

        Command(int a, const std::string& b, const std::string& c, bool r);
    };
    virtual std::string doAction(const Command& aCommand) noexcept = 0;

protected:
    ModuleBase(const std::vector<std::string>& aNameArray) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !MODULE_BASE_HPP
