#include "variable_storage.hpp"

#include "core/logging.hpp"

#include "file_system/file_read.hpp"
#include "file_system/path.hpp"

#include "string/parser.hpp"
#include "string/separators.hpp"

//--------------------------------------------------------------------------------

const int core::VariableStorage::CORRUPTED_VALUE = -100;

core::VariableStorage::VariableStorage() noexcept
{
    registerCommand("set", setCommandHandler);
    registerCommand("show_var", showVarCommandHandler);
    registerCommand("token", tokenCommandHandler);
}

// core::VariableStorage::Variable&
// core::VariableStorage::Variable::operator=(const Variable& other) noexcept
// {
//     value  = int(other.value);
//     parser = other.parser;
//     return *this;
// }

core::VariableStorage::Variable::Variable(const Variable& other) noexcept
{
    value  = int(other.value);
    parser = other.parser;
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::setNonstatic(int a_number, int a_value) noexcept
{
    m_variables[a_number].value = a_value;
}

int
core::VariableStorage::getNonstatic(int a_number) noexcept
{
    return m_variables[a_number].value;
}

//--------------------------------------------------------------------------------

int
core::VariableStorage::addVariableInfoNonstatic(
    const VariableInfoArray& aVarSettings) noexcept
{
    int start_num = m_variables.size();
    m_variables.resize(start_num + aVarSettings.size());

    int num = start_num;
    for (auto& i : aVarSettings)
    {
        m_variables[num].parser    = i.func;
        m_name_to_var_dict[i.name] = num;
        ++num;
    }

    return start_num;
}

void
core::VariableStorage::reloadValuesFromFileNonstatic() noexcept
{
    auto settings = fs::FileRead::getWordsMap(
        fs::ReadFromStoredFile("main_settings.cfg"), str::Separator::variable);
    for (auto& var : settings)
    {
        auto it = m_name_to_var_dict.find(var.first);
        if (it != m_name_to_var_dict.end())
        {
            int num                = it->second;
            m_variables[num].value = m_variables[num].parser(var.second);
            LOG_INFO("Variable", var.first, "set with value", var.second);
        }
        else
        {
            LOG_ERROR("No variable with that name have been registered (",
                      var.first, ")");
        }
    }
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::setCommandHandlerNonstatic(
    core::Command& aCommand) noexcept
{
    for (const auto& i : aCommand.variables)
    {
        // TODO: in separate function
        auto it = m_name_to_var_dict.find(i.first);
        if (it != m_name_to_var_dict.end())
        {
            int num = it->second;
            int val = m_variables[num].parser(i.second);
            if (CORRUPTED_VALUE != val)
            {
                m_variables[num].value = val;
                COMMAND_RETURN_MSG(
                    aCommand,
                    "Successfuly assigned value '%s' to variable '%s'",
                    i.second, i.first);
            }
            else
            {
                COMMAND_RETURN_ERROR(aCommand,
                                     "Unable to set value for '%s' variable: "
                                     "corrupted variable value '%s'",
                                     i.first, i.second);
            }
        }
        else
        {
            COMMAND_RETURN_ERROR(
                aCommand,
                "Unable to set value for '%s' variable: no such variable",
                i.first);
        }
    }
}

void
core::VariableStorage::showVarCommandHandlerNonstatic(
    core::Command& aCommand) noexcept
{
    std::string result;
    for (const auto& i : m_name_to_var_dict)
    {
        result += "\t'";
        result += i.first;
        result += "' = ";
        result += std::to_string(m_variables[i.second].value);
        result += "\n";
    }
    COMMAND_RETURN_MSG(aCommand, "\nVariable list:\n%sList end", result);
}

void
core::VariableStorage::tokenCommandHandlerNonstatic(
    const core::Command& aCommand) noexcept
{
    if (aCommand.arguments.size() != 1)
    {
        LOG_ERROR("Can't parse token arguments. Usage: \"token "
                  "turn_off/turn_on/memory/print\" ");
        return;
    }
    core::CommandHandler::pushCommand(core::Command(
        "set token_state=" + str::string(*aCommand.arguments.begin())));
}
