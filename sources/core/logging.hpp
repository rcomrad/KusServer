#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <ostream>
#include <stdarg.h>
#include <stdio.h>
#include <vector>

#include "domain/holy_trinity.hpp"

#include "string/kus_string.hpp"
#include "string/to_string.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Logging
{
public:
    enum class LogLevel
    {
        Nun,
        Info,
        Warning,
        Error
    };

    enum class OutputType
    {
        Nun,
        Cout,
        Cerr,
        File
    };

    static void setLogLevel(LogLevel aLogLevel) noexcept;
    static void setOutputType(OutputType aOutputType,
                              const str::string& aFileName = "") noexcept;

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

    HOLY_TRINITY_SINGLE(Logging);
    Logging() noexcept;
    ~Logging();
    void clear() noexcept;
    static Logging& getInstance() noexcept;

    //--------------------------------------------------------------------------

    void setOutputTypeNonstatic(OutputType aOutputType,
                                const str::string& aFileName) noexcept;

    //--------------------------------------------------------------------------

    template <typename... Args>
    void writeInfoNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel == LogLevel::Info)
        {
            write("info", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeWarningNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::Warning)
        {
            write("Warn", std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void writeErrorNonstatic(Args&&... args) noexcept
    {
        if (mLogLevel <= LogLevel::Error)
        {
            write("ERROR", std::forward<Args>(args)...);
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
        writeDebugData(aType);
        writeFileName(aFile, 30);
        writeDebugData(aLine, 4);
        writeDebugData(aFunc, 30);
        (void)(writeArg(std::forward<Args>(args)), ...);
        writeEnd();
        fflush(mStream);
    }

    void writeDebugData(const char* arg, int aMaxSize = 0) noexcept;
    void writeDebugData(int arg, int aMaxSize = 0) noexcept;
    void writeFileName(const char* arg, int aMaxSize = 0) noexcept;

    void writeArg(int arg) noexcept;
    void writeArg(const str::string& arg) noexcept;
    void writeArg(const char* arg) noexcept;

    void writeEnd() noexcept;

    //--------------------------------------------------------------------------
};

// clang-format off
#define LOG_INFO(...)     core::Logging::writeInfo    (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)  core::Logging::writeWarning (__FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...)    core::Logging::writeError   (__FILE__, __LINE__, __func__, __VA_ARGS__)
// clang-format on

} // namespace core

#endif // !LOGGING_HPP
