#pragma once

//--------------------------------------------------------------------------------

#include <string_view>
#include <unordered_map>
#include <vector>

#include "kernel/framework/command/include_me.hpp"
#include "kernel/utility/macroses/holy_trinity.hpp"

#include "variable.hpp"

//--------------------------------------------------------------------------------
/*
                                Class contruct

*/
//--------------------------------------------------------------------------------

namespace core
{

class StateStorage;

class VariableStorage : public CommandCaller
{
public:
    VariableStorage();

    void setVariable(int a_number, bool a_value);
    void setVariable(int a_number, int a_value);
    void setVariable(int a_number, const char* a_value);
    void setVariable(int a_number, const std::string& a_value);
    int getVariable(int a_number) const;

    int addVariableInfo(const std::string& a_var_name);
    int addVariableInfo(const std::string& a_var_name,
                        int a_min_value,
                        int a_max_value);
    int addVariableInfo(const std::string& a_var_name,
                        const std::vector<std::string>& a_values);
    int addBoolVariable(const std::string& a_var_name);

    int getCurrentOffset() const noexcept;

protected:
    void init();

private:
    // TODO: LifecycleManager?
    std::vector<Variable> m_variables;
    std::unordered_map<std::string, int> m_name_to_var_dict;

    void varIdCheck(int a_value_num) const;
    void loadVars(core::Command& a_command) const;

    template <typename T>
    void setVariableTamplate(int a_number, T a_value);

    template <typename... Args>
    int addVariableInfoTamplate(const std::string& a_var_name, Args... args);

    COMMAND_HANDLER(setCommandHandler, 0);
    COMMAND_HANDLER(showVarCommandHandler, 1);
    COMMAND_HANDLER(varHelpCommandHandler, 2);
};

} // namespace core

//--------------------------------------------------------------------------------
