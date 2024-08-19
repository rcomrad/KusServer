#include "command_extend.hpp"

//------------------------------------------------------------------------------

core::CommandExtend&
core::CommandExtend::setContext(Context&& a_context) noexcept
{
    m_context = std::move(a_context);
    return *this;
}

//------------------------------------------------------------------------------

core::CommandExtend&
core::CommandExtend::noArgs() noexcept
{
    if (arguments.size())
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(*this, m_context,
                              "Command '%s' does not accept any arguments "
                              "(received '%s' argument).",
                              value, *arguments.begin());
    }
    return *this;
}

core::CommandExtend&
core::CommandExtend::noVars() noexcept
{
    if (variables.size())
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(*this, m_context,
                              "Command '%s' does not accept any variables "
                              "(received '%s'='%s' variable).",
                              value, variables.begin()->first,
                              variables.begin()->second);
    }
    return *this;
}

//------------------------------------------------------------------------------

core::CommandExtend&
core::CommandExtend::hasArgs() noexcept
{
    if (arguments.empty())
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(*this, m_context,
                              "The '%s' command requires arguments.", value)
    }
    return *this;
}

core::CommandExtend&
core::CommandExtend::hasVars() noexcept
{
    if (variables.empty())
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(*this, m_context,
                              "The '%s' command requires variables.", value)
    }
    return *this;
}

//------------------------------------------------------------------------------

core::CommandExtend&
core::CommandExtend::argMinCount(int a_size) noexcept
{
    if (arguments.size() < a_size)
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(
            *this, m_context,
            "The number of arguments for '%s' command is incorrect. "
            "The expected number of arguments is at least %d, "
            "the actual number of arguments is %lu.",
            value, a_size, arguments.size());
    }
    return *this;
}

core::CommandExtend&
core::CommandExtend::varMinCount(int a_size) noexcept
{
    if (variables.size() < a_size)
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(
            *this, m_context,
            "The number of arguments for '%s' command is incorrect. "
            "The expected number of arguments is at least %d, "
            "the actual number of arguments is %lu.",
            value, a_size, variables.size());
    }
    return *this;
}

//------------------------------------------------------------------------------

core::CommandExtend&
core::CommandExtend::argCount(int a_size) noexcept
{
    if (arguments.size() != a_size)
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(
            *this, m_context,
            "The number of arguments for '%s' command is incorrect. "
            "The expected number of arguments is %d, "
            "the actual number of arguments is %lu.",
            value, a_size, arguments.size());
    }
    return *this;
}

core::CommandExtend&
core::CommandExtend::varCount(int a_size) noexcept
{
    if (variables.size() != a_size)
    {
        m_check_result = false;
        PRINT_CMD_CONTEXT_ERR(
            *this, m_context,
            "The number of arguments for '%s' command is incorrect. "
            "The expected number of arguments is %d, "
            "the actual number of arguments is %lu.",
            value, a_size, variables.size());
    }
    return *this;
}

//------------------------------------------------------------------------------

int
core::CommandExtend::getArgumentAsNumber(int a_arg_num) noexcept
{
    return getArgumentAsNumberBase(a_arg_num, 0, false);
}

int
core::CommandExtend::getArgumentAsNumber(int a_arg_num, int a_max_val) noexcept
{
    return getArgumentAsNumberBase(a_arg_num, a_max_val, true);
}

int
core::CommandExtend::getArgumentAsNumberBase(int a_arg_num,
                                             int a_max_val,
                                             bool a_max_check_flag) noexcept
{
    int result = 0;
    argMinCount(a_arg_num);

    if (m_check_result)
    {
        try
        {
            // TODO: remove string
            result = std::stoi(std::string(arguments[a_arg_num]));
        }
        catch (const std::exception& e)
        {
            PRINT_CMD_CONTEXT_ERR(
                *this, m_context,
                "Unable to parse '%s' number, exception '%s'.",
                arguments[a_arg_num], e.what());
            m_check_result = false;
        }

        if (a_max_check_flag && result <= a_max_val)
        {
            PRINT_CMD_CONTEXT_ERR(*this, m_context,
                                  "Too large argument number."
                                  "Expected no more than %lu, got %lu",
                                  a_max_val, result);
            m_check_result = false;
        }
    }

    return result;
}

//------------------------------------------------------------------------------

core::CommandExtend::operator bool() const noexcept
{
    return m_check_result;
}

//------------------------------------------------------------------------------
