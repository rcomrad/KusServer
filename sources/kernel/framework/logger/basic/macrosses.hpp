#pragma once

//------------------------------------------------------------------------------

#include "kernel/utility/defines/define_for_each.hpp"
#include "kernel/utility/file_system/src_path.hpp"
#include "kernel/utility/type/print_helpers/caster.hpp"

#include "level.hpp"
#include "local.hpp"

//------------------------------------------------------------------------------

#define WRITE_LOG_MSG(type, format, ...)                                 \
    core::LocalLogger::getLogger().writeLog(                             \
        core::LogLevel::type, "[%-5s] %-25s| %-30s[%-4d]: " format "\n", \
        #type, __FILENAME__, __func__, __LINE__,                         \
        FOR_EACH(util::PrintCaster::exec, __VA_ARGS__) "");

#define WRITE_TEE_MSG(type, format, ...)   \
    core::LocalLogger::getLogger().teeLog( \
        core::LogLevel::type, format "\n", \
        FOR_EACH(util::PrintCaster::exec, __VA_ARGS__) "");

#define WRITE_LOG(...)              \
    {                               \
        WRITE_LOG_MSG(__VA_ARGS__); \
        WRITE_TEE_MSG(__VA_ARGS__); \
    }

#define LOG_CMD(...)     WRITE_LOG(CMD, __VA_ARGS__)
#define LOG_INFO(...)    WRITE_LOG(INFO, __VA_ARGS__)
#define LOG_WARNING(...) WRITE_LOG(WARN, __VA_ARGS__)
#define LOG_ERROR(...)   WRITE_LOG(ERROR, __VA_ARGS__)
#define LOG_EXEPT(...)   WRITE_LOG(EXEPT, __VA_ARGS__)

//------------------------------------------------------------------------------
