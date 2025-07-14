#pragma once

namespace core
{

enum class LogLevel
{
    NUN,
    CMD,
    INFO,
    WARN,
    ERROR,
    EXEPT
};

extern LogLevel g_log_level;

} // namespace core
