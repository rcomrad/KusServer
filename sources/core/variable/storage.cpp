#include "storage.hpp"

#include "core/logging/logging.hpp"

SINGLETON_DEFINITOR(core, VariableStorage);

//--------------------------------------------------------------------------------

core::VariableStorage::VariableStorage() noexcept
{
    registerCommand("var_set", setCommandHandler,
                    "Assign a value to the specified variable.",
                    "variable_name=variable_value...");
    registerCommand("var_show", showVarCommandHandler,
                    "Print the current value for the specified variable. If no "
                    "name is specified, all variables will be selected.",
                    "[variable_name]...");
    registerCommand("var_help", varHelpCommandHandler,
                    "Print the possible values of the variables. "
                    "If the variable names are not specified, "
                    "print all the variable and their possible values.",
                    "[variable_name]...");
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::setNonstatic(int a_number, int a_value) noexcept
{
    if (a_number >= m_variables.size())
    {
        LOG_ERROR("Wrong variable id")
    }
    else
    {
        m_variables[a_number].value = a_value;
    }
}

int
core::VariableStorage::getNonstatic(int a_number) noexcept
{
    int result = 0;
    if (a_number >= m_variables.size())
    {
        LOG_ERROR("Wrong variable id")
    }
    else
    {
        result = m_variables[a_number].value;
    }
    return result;
}

//--------------------------------------------------------------------------------

int
core::VariableStorage::addVariableInfoNonstatic(
    std::string&& a_var_name,
    FPVariableParser a_func,
    std::vector<std::string>&& a_possable_values) noexcept
{
    int retult = m_variables.size();
    m_variables.emplace_back(std::move(a_var_name), a_func,
                             std::move(a_possable_values));
    m_name_to_var_dict[m_variables.back().name] = retult;
    return retult;
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::setCommandHandlerNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(hasVars().noArgs());

    for (const auto& i : a_command.variables)
    {
        auto it = m_name_to_var_dict.find(i.first);
        if (it != m_name_to_var_dict.end())
        {
            int num = it->second;
            // TODO: multiple output
            auto val = m_variables[num].parser(i.second);
            if (val.has_value())
            {
                m_variables[num].value = val.value();
                PRINT_CMD_MSG(
                    a_command,
                    "Successfully assigned value '%s' to variable '%s'",
                    i.second, i.first);
            }
            else
            {
                PRINT_CMD_ERR(a_command,
                              "Unable to set value for '%s' variable: "
                              "corrupted variable value '%s'",
                              i.first, i.second);
            }
        }
        else
        {
            PRINT_CMD_ERR(
                a_command,
                "Unable to set value for '%s' variable: no such variable",
                i.first);
        }
    }
}

void
core::VariableStorage::showVarCommandHandlerNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(noVars());
    loadVars(a_command);

    std::string result;
    for (const auto& i : a_command.arguments)
    {
        result += "\t'";
        result += i;
        result += "' = ";
        auto it = m_name_to_var_dict.find(i);
        if (it == m_name_to_var_dict.end())
        {
            PRINT_CMD_ERR(a_command, "There is no variable named '%s'.", i);
            return;
        }
        result += std::to_string(m_variables[it->second].value);
        result += "\n";
    }

    // TODO: remove first \n
    PRINT_CMD_MSG(a_command, "\nVariable list:\n%sList end", result);
}

void
core::VariableStorage::varHelpCommandHandlerNonstatic(
    core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(noVars());
    loadVars(a_command);

    std::string result;
    for (const auto& i : a_command.arguments)
    {
        result += "\t'";
        result += i;
        result += "' = ";
        auto it = m_name_to_var_dict.find(i);
        if (it == m_name_to_var_dict.end())
        {
            PRINT_CMD_ERR(a_command, "There is no variable named '%s'.", i);
            return;
        }
        for (auto& j : m_variables[it->second].possable_values)
        {
            result += "'" + j + "' | ";
        }
        result.pop_back();
        result.back() = '\n';
    }

    // TODO: remove first \n
    PRINT_CMD_MSG(a_command, "\nVariable list:\n%sList end", result);
}

void
core::VariableStorage::loadVars(core::CommandExtend& a_command) const noexcept
{
    if (a_command.arguments.empty())
    {
        for (auto& i : m_name_to_var_dict)
        {
            a_command.arguments.push_back(i.first);
        }
    }
}
