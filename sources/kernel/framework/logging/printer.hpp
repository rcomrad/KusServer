#pragma once

#include <cstdarg>
#include <memory>
#include <mutex>
#include <stdio.h>

#include "kernel/framework/command/command.hpp"
#include "kernel/framework/command/command_caller.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Printer : CommandCaller
{
public:
    enum class OutputType
    {
        NUN,
        STDOUT,
        STDERR,
        FILE
    };
    enum class LogLevel
    {
        NUN,
        INFO,
        WARN,
        ERROR,
        CMD
    };

    Printer() noexcept;
    ~Printer();

    void init();

    void setLogLevel(LogLevel aLogLevel) noexcept;
    void setOutputType(OutputType a_output_type,
                       const std::string& a_file_name);

    void writeLog(LogLevel a_level,
                  std::unique_ptr<char[]>* tee_buff,
                  const char* format,
                  ...);

    COMMAND_HANDLER(setLogLevel, 0);
    COMMAND_HANDLER(setLogType, 1);

private:
    bool m_is_file_output;
    LogLevel m_log_level;
    FILE* m_stream;
    std::mutex m_write_mutex;

    void clear() noexcept;
};

} // namespace core
