#include "logging.hpp"

#include <cstdio>
#include <cstring>

//------------------------------------------------------------------------------

void
core::Logging::setLogLevel(core::Logging::LogLevel aOutputType) noexcept
{
    getInstance().mLogLevel = aOutputType;
}

void
core::Logging::setOutputType(core::Logging::OutputType aOutputType,
                             const char* aFileName) noexcept
{
    getInstance().setOutputTypeNonstatic(aOutputType, aFileName);
}

void
core::Logging::setOutputTypeNonstatic(core::Logging::OutputType aOutputType,
                                      const char* aFileName) noexcept
{
    if (OutputType::FILE == aOutputType && '\0' == aFileName[0])
    {
        LOG_ERROR("The name of the log buffer file is not specified, \
            no changes are applied");
        return;
    }

    clear();
    switch (aOutputType)
    {
        case OutputType::STDOUT:
            mStream = stdout;
            LOG_INFO("Log buffer changed to stdout");
            break;
        case OutputType::STDERR:
            mStream = stderr;
            LOG_INFO("Log buffer changed to stderr");
            break;
        case OutputType::FILE:
            mStream       = std::fopen(aFileName, "w");
            mIsFileOutput = true;
            LOG_INFO("Log buffer changed to ", aFileName, " file");
            break;
        default:
            if (mStream == nullptr)
            {
                mStream = stdout;
                LOG_ERROR(
                    "Wrong log buffer type, roll back to default settings "
                    "(stdout)");
            }
            else
            {
                LOG_ERROR(
                    "Wrong log buffer type, roll back to previous settings "
                    "(stdout)");
            }
            break;
    }
}

//------------------------------------------------------------------------------

core::Logging::Logging() noexcept
{
    mIsFileOutput = false;
    mLogLevel     = LogLevel::INFO;
    mStream       = stdout;
}

core::Logging::~Logging()
{
    clear();
}

void
core::Logging::clear() noexcept
{
    fflush(mStream);
    if (mIsFileOutput)
    {
        std::fclose(mStream);
        delete mStream;
        mStream       = nullptr;
        mIsFileOutput = false;
    }
}

core::Logging&
core::Logging::getInstance() noexcept
{
    static Logging instance;
    return instance;
}

//------------------------------------------------------------------------------

void
core::Logging::writeDebugData(int arg) noexcept
{
    // TODO: constexpr
    const int maxSize = 2;
    const int size    = (arg > 10 ? (arg > 100 ? 3 : 2) : 1) / 2;
    std::fprintf(mStream, "[%*d%*s] ", maxSize + size, arg, maxSize - size, "");
}

void
core::Logging::writeDebugData(const char* arg, int aMaxSize, int aSize) noexcept
{
    if (!aSize)
    {
        aSize = std::strlen(arg);
    }
    aSize /= 2;
    std::fprintf(mStream, "[%*s%*s] ", aMaxSize + aSize, arg, aMaxSize - aSize,
                 "");
}

void
core::Logging::writeFileName(const char* arg, int aMaxSize) noexcept
{
    int size = std::strlen(arg);
    int num  = size;
    int cnt  = 0;
    while (num > 0 && cnt < 2)
    {
        if (arg[num] == '/' || arg[num] == '\\')
        {
            ++cnt;
        }
        --num;
    }
    writeDebugData(arg + num + 1, aMaxSize, size - num);
}

void
core::Logging::writeArg(int arg) noexcept
{
    std::fprintf(mStream, "%d ", arg);
}

void
core::Logging::writeArg(double arg) noexcept
{
    std::fprintf(mStream, "%lf ", arg);
}

void
core::Logging::writeArg(const char* arg) noexcept
{
    std::fprintf(mStream, "%s ", arg);
}

void
core::Logging::writeArg(const std::string_view& arg) noexcept
{
    std::fprintf(mStream, "%*s ", arg.length(), arg.data());
}

void
core::Logging::writeEnd() noexcept
{
    std::fprintf(mStream, "\n");
}
