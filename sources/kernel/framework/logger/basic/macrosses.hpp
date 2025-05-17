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

#define LOG_CMD(...)     WRITE_LOG_MSG(CMD, __VA_ARGS__)
#define LOG_INFO(...)    WRITE_LOG_MSG(INFO, __VA_ARGS__)
#define LOG_WARNING(...) WRITE_LOG_MSG(WARN, __VA_ARGS__)
#define LOG_ERROR(...)   WRITE_LOG_MSG(ERROR, __VA_ARGS__)
#define LOG_EXEPT(...)   WRITE_LOG_MSG(EXEPT, __VA_ARGS__)

//------------------------------------------------------------------------------
