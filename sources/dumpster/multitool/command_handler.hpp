#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "core/variable_storage.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace mult
{
class CommandHandler
{
public:
    static std::string process(const crow::request& aReq) noexcept;
    static std::string process(const std::string& aCommand,
                               const std::string& aArgument = "") noexcept;
    // static std::string info(const std::string& aCommand,
    //                            const std::string& aArgument = "") noexcept;
    // static std::string proga(const std::string& aCommand,
    //                            const std::string& aArgument = "") noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
