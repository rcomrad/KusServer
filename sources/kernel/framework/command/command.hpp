#pragma once

//------------------------------------------------------------------------------

#include <set>

#include "command_functor.hpp"

//------------------------------------------------------------------------------

namespace core
{
class Command : public CommandFunctor
{
public:
    template <typename... Args>
    Command(Args... args) noexcept
        : CommandFunctor(std::forward<Args&&>(args)...), m_check_result(true)
    {
    }

    Command& noArgs() noexcept;
    Command& noVars() noexcept;

    Command& hasArgs() noexcept;
    Command& hasVars() noexcept;

    Command& argMinCount(int a_size) noexcept;
    Command& varMinCount(int a_size) noexcept;

    Command& argCount(int a_size) noexcept;
    Command& varCount(int a_size) noexcept;

    Command& argCount(const std::set<int>& a_sizes) noexcept;

    int getArgumentAsNumber(int a_arg_num) noexcept;
    int getArgumentAsNumber(int a_arg_num, int a_max_val) noexcept;

    operator bool() const noexcept;

private:
    bool m_check_result;

    int getArgumentAsNumberBase(int a_arg_num,
                                int a_max_val,
                                bool a_max_check_flag) noexcept;
};

} // namespace core

//------------------------------------------------------------------------------
