#pragma once

//------------------------------------------------------------------------------

#include "utility/common/define_for_each.hpp"

#include "context.hpp"
#include "definitions.hpp"
#include "logging_functors.hpp"
#include "printer.hpp"

//------------------------------------------------------------------------------

#define WRITE_LOG_MSG(type, context, tee_buff, format, ...)            \
    {                                                                  \
        core::Printer::getInstance().write(                            \
            core::LogLevel::type, tee_buff,                            \
            "[%-5s] %-25s| %-30s[%-4d] " format "\n", #type,           \
            context.file_name, context.func_name, context.line_num,    \
            FOR_EACH(core::LoggingFunctors::convert, __VA_ARGS__) ""); \
    }

#define WRITE_LOG_MSG_BASE(type, context, format, ...) \
    WRITE_LOG_MSG(type, context, NULL, format, __VA_ARGS__)

#define LOG_INFO(...)                                        \
    {                                                        \
        DECLARE_LOCAL_CONTEXT;                               \
        WRITE_LOG_MSG_BASE(INFO, context_local, __VA_ARGS__) \
    }
#define LOG_WARNING(...)                                     \
    {                                                        \
        DECLARE_LOCAL_CONTEXT;                               \
        WRITE_LOG_MSG_BASE(WARN, context_local, __VA_ARGS__) \
    }
#define LOG_ERROR(...)                                        \
    {                                                         \
        DECLARE_LOCAL_CONTEXT;                                \
        WRITE_LOG_MSG_BASE(ERROR, context_local, __VA_ARGS__) \
    }

#define CONTEXT_INFO(context, ...) \
    WRITE_LOG_MSG_BASE(INFO, context, __VA_ARGS__)
#define CONTEXT_WARNING(context, ...) \
    WRITE_LOG_MSG_BASE(WARN, context, __VA_ARGS__)
#define CONTEXT_ERROR(context, ...) \
    WRITE_LOG_MSG_BASE(ERROR, context, __VA_ARGS__)

// TODO: more use of LOG_CATCH
#define LOG_CATCH(func, cotext, msg, ...)                                      \
    try                                                                        \
    {                                                                          \
        func;                                                                  \
    }                                                                          \
    catch (const std::exception& e)                                            \
    {                                                                          \
        CONTEXT_ERROR(cotext, msg " Exception: '%s'.", __VA_ARGS__, e.what()); \
    }                                                                          \
    catch (...)                                                                \
    {                                                                          \
                                                                               \
        CONTEXT_ERROR(cotext, msg " Unknown exception.", __VA_ARGS__);         \
    }

//------------------------------------------------------------------------------
