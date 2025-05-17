#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>

#include "core/command/definitions.hpp"
#include "core/command/register.hpp"

#include "utility/common/holy_trinity.hpp"

#include "variable.hpp"

//--------------------------------------------------------------------------------
/*
                                Class contruct

*/
//--------------------------------------------------------------------------------

namespace core
{

class VariableStorage : public CommandRegister
{
public:
    HOLY_TRINITY_SINGLETON(VariableStorage);

    SINGL_RET_METHOD(int,
                     addVariableInfo,
                     (const char* a_var_name,
                      const char** a_values,
                      int a_value_count));

    SINGL_VOID_METHOD(set, (int aNumber, int aValue));
    SINGL_RET_METHOD(int, get, (int aNumber));

private:
    std::vector<Variable> m_variables;
    std::unordered_map<std::string_view, int> m_name_to_var_dict;

    VariableStorage() noexcept;
    COMMAND_HANDLER_NONSTATIC(setCommandHandler);
    COMMAND_HANDLER_NONSTATIC(showVarCommandHandler);
    COMMAND_HANDLER_NONSTATIC(varHelpCommandHandler);

    void loadVars(core::CommandExtend& a_command) const noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
