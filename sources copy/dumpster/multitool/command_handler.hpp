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
    static str::String process(const str::String& aCommand,
                               const str::String& aArgument = "") noexcept;
    // static str::String info(const str::String& aCommand,
    //                            const str::String& aArgument = "") noexcept;
    // static str::String proga(const str::String& aCommand,
    //                            const str::String& aArgument = "") noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
