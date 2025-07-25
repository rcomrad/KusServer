#include "storage.hpp"

#include "kernel/framework/command/include_me.hpp"
#include "kernel/framework/command/state_storage.hpp"
#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/include_me.hpp"

//--------------------------------------------------------------------------------

template <typename T>
void
core::VariableStorage::setVariableTamplate(int a_number, T a_value)
{
    varIdCheck(a_number);
    m_variables[a_number].obj.setValue(a_value);
}

template <typename... Args>
int
core::VariableStorage::addVariableInfoTamplate(const std::string& a_var_name,
                                               Args... args)
{
    const std::lock_guard lock(m_var_info_mutex);

    // TODO: make it pretty
    auto it = m_name_to_var_dict.find(a_var_name);
    if (it == m_name_to_var_dict.end())
    {
        int id = m_var_cnt++;
        if (id >= m_variables.size())
        {
            THROW("The maximum number of preallocated variables has been "
                  "exceeded");
        }

        it = m_name_to_var_dict.emplace(a_var_name, id).first;
        m_variables[id].create(a_var_name, args...);
    }
    else
    {
        LOG_INFO("Use already existing %s variable", a_var_name);

        int id = it->second;
        VariableCell old(m_variables[id].obj);
        m_variables[id].destroy();
        m_variables[id].create(a_var_name, args...);
        m_variables[id].obj.setValue(old);
    }

    return it->second;
}

//--------------------------------------------------------------------------------

// TODO: m_variables allocation settings
core::VariableStorage::VariableStorage() : m_var_cnt(0), m_variables(100)
{
}

void
core::VariableStorage::init()
{
    // TODO: -f
    registrateBaseCommand("var_set",
                          "Assign a value to the specified variable.",
                          "variable_name=variable_value...");
    registrateBaseCommand(
        "var_show",
        "Print the current value for the specified variable. If no "
        "name is specified, all variables will be selected.",
        "[variable_name]...");
    registrateBaseCommand("var_help",
                          "Print the possible values of the variables. "
                          "If the variable names are not specified, "
                          "print all the variable and their possible values.",
                          "[variable_name]...");

    KERNEL.listenCommand("var_set", StateStorage::StateType::MERGE_VARS |
                                        StateStorage::StateType::MERGE_ARGS);
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::varIdCheck(int a_value_num) const
{
    if (a_value_num >= m_var_cnt)
    {
        THROW("No variable with id {} - id too large, max id is {}",
              a_value_num, m_var_cnt - 1);
    }
}

void
core::VariableStorage::setVariable(int a_number, bool a_value)
{
    setVariableTamplate(a_number, a_value);
}

void
core::VariableStorage::setVariable(int a_number, int a_value)
{
    setVariableTamplate(a_number, a_value);
}

void
core::VariableStorage::setVariable(int a_number, std::string_view a_value)
{
    setVariableTamplate(a_number, a_value);
}

int
core::VariableStorage::getVariable(int a_number) const
{
    varIdCheck(a_number);
    return m_variables[a_number].obj.getValue();
}

//--------------------------------------------------------------------------------

int
core::VariableStorage::addVariableInfo(const std::string& a_var_name)
{
    return addVariableInfoTamplate(a_var_name);
}

int
core::VariableStorage::addVariableInfo(const std::string& a_var_name,
                                       int a_min_value,
                                       int a_max_value)
{
    return addVariableInfoTamplate(a_var_name, a_min_value, a_max_value);
}

int
core::VariableStorage::addVariableInfo(const std::string& a_var_name,
                                       const std::vector<std::string>& a_values)
{
    return addVariableInfoTamplate(a_var_name, a_values);
}

int
core::VariableStorage::addBoolVariable(const std::string& a_var_name)
{
    return addVariableInfoTamplate(a_var_name, true);
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::setCommandHandler(core::Command& a_command)
{
    a_command.hasVars().argCount({0, 1});

    bool force = a_command.hasArg("-f");

    for (const auto& i : a_command.variables)
    {
        auto it = m_name_to_var_dict.find(i.first);
        if (it == m_name_to_var_dict.end())
        {
            if (!force)
            {
                continue;
            }

            addVariableInfo(i.first);
            it = m_name_to_var_dict.find(i.first);
        }

        int num   = it->second;
        auto& var = m_variables[num].obj;
        var.setValue(i.second);

        // TODO: multiple output
        // LOG_CMD("Successfully assigned value '%s' (%d) to variable '%s'",
        //         it->second, var.getValue(), it->first);
    }

    LOG_CMD("Successfully assigned variable values");
}

void
core::VariableStorage::showVarCommandHandler(core::Command& a_command)
{
    a_command.noVars();
    loadVars(a_command);

    const std::lock_guard lock(m_var_info_mutex);

    std::string result;
    for (const auto& i : a_command.arguments)
    {
        auto it = m_name_to_var_dict.find(i);
        if (it == m_name_to_var_dict.end())
        {
            LOG_ERROR("There is no variable named '%s'.", i);
            return;
        }
        m_variables[it->second].obj.addValueInfo(result);
    }

    // TODO: remove first \n
    LOG_CMD("Variable list:\n%sList end", result);
}

void
core::VariableStorage::varHelpCommandHandler(core::Command& a_command)
{
    a_command.noVars();
    loadVars(a_command);

    const std::lock_guard lock(m_var_info_mutex);

    std::string result;
    for (const auto& i : a_command.arguments)
    {
        auto it = m_name_to_var_dict.find(i);
        if (it == m_name_to_var_dict.end())
        {
            LOG_ERROR("There is no variable named '%s'.", i);
            return;
        }
        m_variables[it->second].obj.addValueMap(result);
    }

    // TODO: remove first \n
    LOG_CMD("Variable list:\n%sList end", result);
}

void
core::VariableStorage::loadVars(core::Command& a_command) const
{
    if (a_command.arguments.empty())
    {
        const std::lock_guard lock(m_var_info_mutex);

        for (auto& i : m_name_to_var_dict)
        {
            a_command.arguments.push_back(i.first);
        }
    }
}
