#pragma once

//--------------------------------------------------------------------------------

#include <string_view>
#include <unordered_map>
#include <vector>

#include "kernel/framework/command/include_me.hpp"
// #include "kernel/utility/common/exception.hpp"
#include "kernel/utility/defines/holy_trinity.hpp"

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

    void setVariable(size_t a_number, bool a_value);
    void setVariable(size_t a_number, int a_value);
    void setVariable(size_t a_number, const char* a_value);
    void setVariable(size_t a_number, const std::string& a_value);
    int getVariable(size_t a_number) const;

    size_t addVariableInfo(const std::string& a_var_name);
    size_t addVariableInfo(const std::string& a_var_name,
                           int a_min_value,
                           int a_max_value);
    size_t addVariableInfo(const std::string& a_var_name,
                           const std::vector<std::string>& a_values);
    size_t addBoolVariable(const std::string& a_var_name);

    size_t getCurrentOffset() const noexcept;

protected:
    void init();

private:
    // TODO: LifecycleManager?
    std::vector<Variable> m_variables;
    std::unordered_map<std::string, int> m_name_to_var_dict;

    void varIdCheck(size_t a_value_num) const;
    void loadVars(core::Command& a_command) const;

    template <typename T>
    void setVariableTamplate(size_t a_number, T a_value);
    // {
    //     varIdCheck(a_number);
    //     if (!m_variables[a_number].setValue(a_value))
    //     {
    //         // THROW("Failed to set value '{}' for '{}' variable.",
    //         a_value,
    //         //       m_variables[a_number].getName());
    //     }
    // }

    template <typename... Args>
    size_t addVariableInfoTamplate(const std::string& a_var_name, Args... args);
    // {
    //     size_t retult = m_variables.size();
    //     m_variables.emplace_back(a_var_name, args...);
    //     m_name_to_var_dict[a_var_name] = retult;
    //     return retult;
    // }

    COMMAND_HANDLER(setCommandHandler, 0);
    COMMAND_HANDLER(showVarCommandHandler, 1);
    COMMAND_HANDLER(varHelpCommandHandler, 2);
};

} // namespace core

//--------------------------------------------------------------------------------
