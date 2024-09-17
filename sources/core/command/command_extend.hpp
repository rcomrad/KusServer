#pragma once

//------------------------------------------------------------------------------

#include <set>

#include "core/logging/logging.hpp"

#include "command.hpp"

//------------------------------------------------------------------------------

namespace core
{
struct CommandExtend : public Command
{
    template <typename... Args>
    CommandExtend(Args... args) noexcept
        : Command(std::forward<Args&&>(args)...), m_check_result(true)
    {
    }

    CommandExtend& setContext(Context&& a_context) noexcept;

    CommandExtend& noArgs() noexcept;
    CommandExtend& noVars() noexcept;

    CommandExtend& hasArgs() noexcept;
    CommandExtend& hasVars() noexcept;

    CommandExtend& argMinCount(int a_size) noexcept;
    CommandExtend& varMinCount(int a_size) noexcept;

    CommandExtend& argCount(int a_size) noexcept;
    CommandExtend& varCount(int a_size) noexcept;

    CommandExtend& argCount(const std::set<int>& a_sizes) noexcept;

    int getArgumentAsNumber(int a_arg_num) noexcept;
    int getArgumentAsNumber(int a_arg_num, int a_max_val) noexcept;

    operator bool() const noexcept;

private:
    bool m_check_result;
    Context m_context;

    int getArgumentAsNumberBase(int a_arg_num,
                                int a_max_val,
                                bool a_max_check_flag) noexcept;
};

using FP_CommandHandler = void (*)(CommandExtend&);

} // namespace core

//------------------------------------------------------------------------------

#define COMMAND_HANDLER(name) \
    static void name(core::CommandExtend& a_command) noexcept
#define COMMAND_HANDLER_NONSTATIC(name)                              \
    void name##Nonstatic(core::CommandExtend& a_command) noexcept;   \
    static inline void name(core::CommandExtend& a_command) noexcept \
    {                                                                \
        getInstance().name##Nonstatic(a_command);                    \
    }

//------------------------------------------------------------------------------

#define WRITE_LOG_MSG_CMD(type, context, cmd, format, ...)           \
    WRITE_LOG_MSG(type, context, (&((cmd).m_result_buffer)), format, \
                  __VA_ARGS__)

#define PRINT_CMD_MSG(name, ...)                                   \
    {                                                              \
        DECLARE_LOCAL_CONTEXT;                                     \
        WRITE_LOG_MSG_CMD(CMD, context_local, (name), __VA_ARGS__) \
    }

#define PRINT_CMD_ERR(name, ...)                                     \
    {                                                                \
        DECLARE_LOCAL_CONTEXT;                                       \
        WRITE_LOG_MSG_CMD(ERROR, context_local, (name), __VA_ARGS__) \
    }

#define PRINT_CMD_CONTEXT_MSG(name, context, ...) \
    WRITE_LOG_MSG_CMD(CMD, context, (name), __VA_ARGS__)
#define PRINT_CMD_CONTEXT_ERR(name, context, ...) \
    WRITE_LOG_MSG_CMD(ERROR, context, (name), __VA_ARGS__)

//------------------------------------------------------------------------------

#define CMD_ASSERT(...)                                   \
    if (!a_command.setContext(LOCAL_CONTEXT).__VA_ARGS__) \
    {                                                     \
        return;                                           \
    }

#define CMD_GET_ARG_AS_NUM(name, ...)                                     \
    a_command.setContext(LOCAL_CONTEXT).getArgumentAsNumber(__VA_ARGS__); \
    if (!a_command)                                                       \
    {                                                                     \
        return;                                                           \
    }
