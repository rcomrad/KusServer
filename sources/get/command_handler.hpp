#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "crow.h"

//--------------------------------------------------------------------------------

namespace get
{
class CommandHandler
{
public:
    static std::string process(const std::string& aType,
                               const std::string& aValue) noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
