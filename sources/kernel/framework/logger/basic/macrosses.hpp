#pragma once

//------------------------------------------------------------------------------

#include "kernel/framework/file_system/src_path.hpp"
#include "kernel/utility/macroses/define_for_each.hpp"
#include "kernel/utility/type/print_helpers/caster.hpp"

#include "level.hpp"
#include "local.hpp"

//------------------------------------------------------------------------------

#define WRITE_LOG_MSG_BASE(type, func_name, line_num, format, ...)       \
    core::LocalLogger::getLogger().writeLog(                             \
        core::LogLevel::type, "[%-5s] %-30s| %-30s[%-4d]: " format "\n", \
        #type, __FILENAME__, func_name, line_num,                        \
        FOR_EACH(utils::PrintCaster::exec, __VA_ARGS__) "");

#define WRITE_LOG_MSG(type, format, ...) \
    WRITE_LOG_MSG_BASE(type, __func__, __LINE__, format, __VA_ARGS__)

#define WRITE_TEE_MSG(type, format, ...)   \
    core::LocalLogger::getLogger().teeLog( \
        core::LogLevel::type, format "\n", \
        FOR_EACH(utils::PrintCaster::exec, __VA_ARGS__) "");

#define WRITE_LOG(...)              \
    {                               \
        WRITE_LOG_MSG(__VA_ARGS__); \
        WRITE_TEE_MSG(__VA_ARGS__); \
    }

#define LOG_DEBUG(...)   WRITE_LOG(DEBUG, __VA_ARGS__)
#define LOG_CMD(...)     WRITE_LOG(CMD, __VA_ARGS__)
#define LOG_TRACE(...)   WRITE_LOG(TRACE, __VA_ARGS__)
#define LOG_INFO(...)    WRITE_LOG(INFO, __VA_ARGS__)
#define LOG_WARNING(...) WRITE_LOG(WARN, __VA_ARGS__)
#define LOG_ERROR(...)   WRITE_LOG(ERROR, __VA_ARGS__)
#define LOG_EXEPT(...)   WRITE_LOG(EXEPT, __VA_ARGS__)

// TODO: ~this from C++23
#define KUS_SCOPED_TRACE(...)                                   \
    struct ScopedTraceLog                                       \
    {                                                           \
        ScopedTraceLog(const char* a_func_name, int a_line_num) \
            : func_name(a_func_name), line_num(a_line_num)      \
        {                                                       \
            WRITE_LOG_MSG_BASE(DEBUG, func_name, line_num,      \
                               "Start " __VA_ARGS__);           \
        }                                                       \
        ~ScopedTraceLog()                                       \
        {                                                       \
            WRITE_LOG_MSG_BASE(DEBUG, func_name, line_num,      \
                               "\tEnd " __VA_ARGS__);           \
        }                                                       \
        int line_num;                                           \
        const char* func_name;                                  \
    } ___scoped_trace_log(__func_name, __line_num);

#define SCOPED_TRACE_BASIC(...)  \
    auto __line_num  = __LINE__; \
    auto __func_name = __func__; \
    KUS_SCOPED_TRACE(__VA_ARGS__)

#define SCOPED_TRACE_INIT(name)   SCOPED_TRACE_BASIC(name " initialization")
#define SCOPED_TRACE_CREATE(name) SCOPED_TRACE_BASIC(name " creation")
#define SCOPED_TRACE_TERM(name)   SCOPED_TRACE_BASIC(name " termination")
#define SCOPED_TRACE_FUNC(name)   SCOPED_TRACE_BASIC(name " function")

//------------------------------------------------------------------------------
