#pragma once

//------------------------------------------------------------------------------

#include "command.hpp"

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

//------------------------------------------------------------------------------
