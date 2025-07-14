#include "command.hpp"

//------------------------------------------------------------------------------

#include "kernel/framework/logger/include_me.hpp"

//------------------------------------------------------------------------------

core::Command&
core::Command::noArgs() noexcept
{
    if (m_check_result && arguments.size())
    {
        m_check_result = false;
        LOG_ERROR("Command '%s' does not accept any arguments "
                  "(received '%s' argument).",
                  value, *arguments.begin());
    }
    return *this;
}

core::Command&
core::Command::noVars() noexcept
{
    if (m_check_result && variables.size())
    {
        m_check_result = false;
        LOG_ERROR("Command '%s' does not accept any variables "
                  "(received '%s'='%s' variable).",
                  value, variables.begin()->first, variables.begin()->second);
    }
    return *this;
}

//------------------------------------------------------------------------------

core::Command&
core::Command::hasArgs() noexcept
{
    if (m_check_result && arguments.empty())
    {
        m_check_result = false;
        LOG_ERROR("The '%s' command requires arguments.", value)
    }
    return *this;
}

core::Command&
core::Command::hasVars() noexcept
{
    if (m_check_result && variables.empty())
    {
        m_check_result = false;
        LOG_ERROR("The '%s' command requires variables.", value)
    }
    return *this;
}

//------------------------------------------------------------------------------

core::Command&
core::Command::argMinCount(int a_size) noexcept
{
    if (m_check_result && arguments.size() < a_size)
    {
        m_check_result = false;
        LOG_ERROR("The number of arguments for '%s' command is incorrect. "
                  "The expected number of arguments is at least %d, "
                  "the actual number of arguments is %lu.",
                  value, a_size, arguments.size());
    }
    return *this;
}

core::Command&
core::Command::varMinCount(int a_size) noexcept
{
    if (m_check_result && variables.size() < a_size)
    {
        m_check_result = false;
        LOG_ERROR("The number of arguments for '%s' command is incorrect. "
                  "The expected number of arguments is at least %d, "
                  "the actual number of arguments is %lu.",
                  value, a_size, variables.size());
    }
    return *this;
}

//------------------------------------------------------------------------------

core::Command&
core::Command::argCount(int a_size) noexcept
{
    std::set<int> args_cnt{a_size};
    return argCount(args_cnt);
}

core::Command&
core::Command::varCount(int a_size) noexcept
{
    if (m_check_result && variables.size() != a_size)
    {
        m_check_result = false;
        LOG_ERROR("The number of variables for '%s' command is incorrect. "
                  "The expected number of variables is %d, "
                  "the actual number of variables is %lu.",
                  value, a_size, variables.size());
    }
    return *this;
}

core::Command&
core::Command::argCount(const std::set<int>& a_sizes) noexcept
{
    if (m_check_result && !a_sizes.count(arguments.size()))
    {
        std::string expect;
        for (auto i : a_sizes)
        {
            if (!expect.empty())
            {
                expect += " or ";
            }
            expect += std::to_string(i);
        }
        m_check_result = false;
        LOG_ERROR("The number of arguments for '%s' command is incorrect. "
                  "The expected number of arguments is %s, "
                  "the actual number of arguments is %lu.",
                  value, expect, arguments.size());
    }
    return *this;
}

//------------------------------------------------------------------------------

int
core::Command::getArgumentAsNumber(int a_arg_num) noexcept
{
    return getArgumentAsNumberBase(a_arg_num, 0, false);
}

int
core::Command::getArgumentAsNumber(int a_arg_num, int a_max_val) noexcept
{
    return getArgumentAsNumberBase(a_arg_num, a_max_val, true);
}

int
core::Command::getArgumentAsNumberBase(int a_arg_num,
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
            // TODO: stoi not check everything
            result = std::stoi(std::string(arguments[a_arg_num]));
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Unable to parse '%s' number, exception '%s'.",
                      arguments[a_arg_num], e.what());
            m_check_result = false;
        }

        if (a_max_check_flag && result >= a_max_val)
        {
            LOG_ERROR("Too large argument number."
                      "Expected no more than %lu, got %lu",
                      a_max_val, result);
            m_check_result = false;
        }
    }

    return result;
}

//------------------------------------------------------------------------------

core::Command::
operator bool() const noexcept
{
    return m_check_result;
}

//------------------------------------------------------------------------------
