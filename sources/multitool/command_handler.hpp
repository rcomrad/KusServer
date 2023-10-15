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
    static std::string process(const std::string& aType,
                               const std::string& aValue = "") noexcept;

private:
    static std::unordered_map<
        std::string,
        std::function<std::string(const std::string& aValue)>>
        mSpecialRoutes;
    static std::unordered_set<std::string> mLegaCommands;

    template <typename T>
    static std::string applyCommand(const std::string& aName,
                                    const T& aValue) noexcept
    {
        core::VariableStorage::setVariable(aName, aValue, 0ms);

        static auto& executedCommand =
            core::VariableStorage::touchWord("executed_command");
        while (executedCommand != aName)
            ;

        static auto& executedResult =
            core::VariableStorage::touchWord("command_result");
        auto result = executedResult;
        core::VariableStorage::setVariable("command_result", "", 0ms);

        return result;
    }

    static std::string restart(const std::string& aValue) noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
