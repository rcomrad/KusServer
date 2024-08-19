#pragma once

#include <cstdarg>
#include <memory>
#include <mutex>
#include <stdio.h>

#include "utility/common/holy_trinity.hpp"

#include "definitions.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Printer
{
public:
    HOLY_TRINITY_SINGLETON(Printer);

    enum class OutputType
    {
        NUN,
        STDOUT,
        STDERR,
        FILE
    };

    static void setLogLevel(LogLevel aLogLevel) noexcept;
    SINGL_VOID_METHOD(setOutputType,
                      (OutputType aOutputType, const std::string& aFileName));

    void write(LogLevel a_level, std::unique_ptr<char[]>* tee_buff, const char* format, ...);

private:
    bool mIsFileOutput;
    LogLevel mLogLevel;
    FILE* mStream;
    std::mutex m_write_mutex;

    Printer() noexcept;
    ~Printer();
    void clear() noexcept;
};

} // namespace core
