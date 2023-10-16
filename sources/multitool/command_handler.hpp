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

    template <typename T>
    static std::string applyCommand(const std::string& aName,
                                    const T& aValue) noexcept
    {
        static auto& executedCommand =
            core::VariableStorage::touchWord("executed_command");
        static auto& executedResult =
            core::VariableStorage::touchWord("command_result");

        core::VariableStorage::setVariable(aName, aValue, 0ms);

        while (executedCommand != aName)
            ;
        auto result = executedResult;
        core::VariableStorage::setVariable("command_result", "", 0ms);
        core::VariableStorage::setVariable("executed_command", "", 0ms);

        return result;
    }

private:
    static std::unordered_map<
        std::string,
        std::function<std::string(const std::string& aValue)>>
        mSpecialRoutes;
    static std::unordered_set<std::string> mLegaCommands;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !COMMAND_HANDLER_HPP
