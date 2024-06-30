#pragma once

#include <stdio.h>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Logging
{
public:
    HOLY_TRINITY_SINGLETON(Logging);

    enum class LogLevel
    {
        NUN,
        INFO,
        WARNING,
        ERROR
    };

    enum class OutputType
    {
        NUN,
        STDOUT,
        STDERR,
        FILE
    };

    static void setLogLevel(LogLevel aLogLevel) noexcept;
    SINGL_VOID_METHOD(setOutputType,
                      (OutputType aOutputType, const str::string& aFileName));

    //--------------------------------------------------------------------------

    template <typename... Args>
    void writeInfo(Args&&... args) noexcept
    {
        if (mLogLevel == LogLevel::INFO)
        {
            write("info", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeWarning(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::WARNING)
        {
            write("WARN", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeError(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::ERROR)
        {
            write("ERROR!", std::forward<Args>(args)...);
        }
    }

private:
    bool mIsFileOutput;
    LogLevel mLogLevel;
    FILE* mStream;

    //--------------------------------------------------------------------------

    Logging() noexcept;
    ~Logging();
    void clear() noexcept;

    //--------------------------------------------------------------------------

    template <typename... Args>
    void write(const char* aType,
               const char* aFile,
               int aLine,
               const char* aFunc,
               Args&&... args) noexcept
    {
        writeDebugData(aType, 4);
        writeFileName(aFile, 15);
        writeDebugData(aLine);
        writeDebugData(aFunc, 15);
        (void)(writeArg(std::forward<Args>(args)), ...);
        writeEnd();
        fflush(mStream); // TODO: remove
    }

    void writeDebugData(int arg) noexcept;
    void writeDebugData(const char* arg,
                        int aMaxSize = 0,
                        int aSize    = 0) noexcept;
    void writeFileName(const char* arg, int aMaxSize = 0) noexcept;

    void writeArg(int arg) noexcept;
    void writeArg(double arg) noexcept;
    void writeArg(const str::string& arg) noexcept;
    void writeArg(const char* arg) noexcept;

    void writeEnd() noexcept;

    //--------------------------------------------------------------------------
};

// clang-format off
#define LOG_INFO(...)     core::Logging::getInstance().writeInfo    (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)  core::Logging::getInstance().writeWarning (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...)    core::Logging::getInstance().writeError   (__FILE__, __LINE__, __func__, __VA_ARGS__)
// clang-format on

} // namespace core
