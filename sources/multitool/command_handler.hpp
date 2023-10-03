#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

#include "crow.h"

//--------------------------------------------------------------------------------

namespace mult
{
class CommandHandler
{
public:
    static std::string process(const crow::request& aReq) noexcept;
    static std::string process(const std::string& aType,
                               const std::string& aValue) noexcept;

private:
    static std::string restart(const std::string aValue) noexcept;
    static std::string tokenHandler(const std::string aValue) noexcept;
    static std::string kill(const std::string aValue) noexcept;
    static std::string dump(const std::string aValue) noexcept;
    static std::string question(const std::string aValue) noexcept;

    static std::string loadQuestions() noexcept;
    static std::string retestQuestions() noexcept;

    static std::unordered_map<std::string,
                              decltype(&mult::CommandHandler::restart)>
        mRouterMap;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
