#pragma once

namespace core
{

enum class LogLevel
{
    NUN,
    SPAM,
    CMD, // todo: swap with TRACE
    TRACE,
    INFO,
    WARN,
    ERROR,
    EXEPT
};

extern LogLevel g_log_level;

} // namespace core
