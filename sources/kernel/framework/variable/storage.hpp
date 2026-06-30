#pragma once

//--------------------------------------------------------------------------------

#include "kernel/framework/command/include_me.hpp"
#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/utility/macroses/holy_trinity.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

#include <atomic>
#include <mutex>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "variable_cell.hpp"

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
    void setVariable(int a_number, std::string_view a_value);
    void setVariable(int a_number, const char* a_value);

    template <typename T>
    void setVariable(const std::string& a_name, T a_value)
    {
        auto it = m_name_to_var_dict.find(a_name);
        if (it == m_name_to_var_dict.end())
        {
            THROW("No such variable: %s", a_name);
        }
        setVariable(it->second, a_value);
    }

    int getVariable(int a_number) const;
    int getVariable(const std::string& a_name);

    int addVariableInfo(const std::string& a_var_name);
    int addVariableInfo(const std::string& a_var_name, int a_default_value);
    int addVariableInfo(const std::string& a_var_name,
                        int a_min_value,
                        int a_max_value);
    int addVariableInfo(const std::string& a_var_name,
                        int a_default_value,
                        int a_min_value,
                        int a_max_value);
    int addVariableInfo(const std::string& a_var_name,
                        const std::vector<std::string>& a_values);

    int addBoolVariable(const std::string& a_var_name, bool a_value);
    int addVariableInfo(bool a_value, const std::string& a_var_name);

protected:
    void init();

private:
    mutable std::mutex m_var_info_mutex;
    std::atomic<int> m_var_cnt;
    std::vector<utils::LifecycleManager<VariableCell>> m_variables;
    std::unordered_map<std::string, int> m_name_to_var_dict;

    void varIdCheck(int a_value_num) const;
    void loadVars(core::Command& a_command) const;

    template <typename T>
    void setVariableTamplate(int a_number, T a_value);

    template <typename TDefaultValue, typename... Args>
    int addVariableInfoTamplate(const std::string& a_var_name,
                                std::optional<TDefaultValue> a_default_value,
                                Args... args);

    COMMAND_HANDLER(setCommandHandler, 0);
    COMMAND_HANDLER(showVarCommandHandler, 1);
    COMMAND_HANDLER(varHelpCommandHandler, 2);
};

} // namespace core

//--------------------------------------------------------------------------------
