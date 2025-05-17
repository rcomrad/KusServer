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
    static str::String process(const crow::request& aReq) noexcept;
    static str::String process(const char* aCommand,
                               const char* aArgument = "") noexcept;
    // static str::String info(const char* aCommand,
    //                            const char* aArgument = "") noexcept;
    // static str::String proga(const char* aCommand,
    //                            const char* aArgument = "") noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
