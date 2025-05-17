#pragma once

#include <stdio.h>
#include <string_view>
#include <utility>

#include "holy_trinity.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Logging
{
public:
    HOLY_TRINITY_SINGLE(Logging);

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
    static void setOutputType(OutputType aOutputType,
                              const char* aFileName = "") noexcept;

    //--------------------------------------------------------------------------

    template <typename... Args>
    static void writeInfo(Args&&... args) noexcept
    {
        getInstance().writeInfoNonstatic(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void writeWarning(Args&&... args) noexcept
    {
        getInstance().writeWarningNonstatic(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void writeError(Args&&... args) noexcept
    {
        getInstance().writeErrorNonstatic(std::forward<Args>(args)...);
    }

private:
    bool mIsFileOutput;
    LogLevel mLogLevel;
    FILE* mStream;

    //--------------------------------------------------------------------------

    Logging() noexcept;
    ~Logging();
    void clear() noexcept;
    static Logging& getInstance() noexcept;

    //--------------------------------------------------------------------------

    void setOutputTypeNonstatic(OutputType aOutputType,
                                const char* aFileName) noexcept;

    //--------------------------------------------------------------------------

    template <typename... Args>
    void writeInfoNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel == LogLevel::INFO)
        {
            write("info", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeWarningNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::WARNING)
        {
            write("WARN", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeErrorNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::ERROR)
        {
            write("ERROR!", std::forward<Args>(args)...);
        }
    }

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
    void writeArg(const char* arg) noexcept;
    void writeArg(const std::string_view& arg) noexcept;

    void writeEnd() noexcept;

    //--------------------------------------------------------------------------
};

enum
{
    LOG_BUFFER_SIZE = 200
};

#define arr(...)                          \
    {                                     \
        char log_buffer[LOG_BUFFER_SIZE]; \
    }

// clang-format off
#define LOG_INFO(...)     core::Logging::writeInfo    (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)  core::Logging::writeWarning (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...)    core::Logging::writeError   (__FILE__, __LINE__, __func__, __VA_ARGS__)
// clang-format on

} // namespace core
