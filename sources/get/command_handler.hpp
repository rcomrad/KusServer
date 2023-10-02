#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

#include "crow.h"

//--------------------------------------------------------------------------------

namespace get
{
class CommandHandler
{
public:
    static std::string process(const std::string& aType,
                               const std::string& aValue) noexcept;

private:
    static std::string restart(const std::string aValue) noexcept;
    static std::string tokenHandler(const std::string aValue) noexcept;
    static std::string kill(const std::string aValue) noexcept;
    // static std::string check(const std::string aValue) noexcept;
    // static std::string time(const std::string aValue) noexcept;
    static std::string dump(const std::string aValue) noexcept;

    static std::unordered_map<std::string,
                              decltype(&get::CommandHandler::restart)>
        mRouterMap;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
