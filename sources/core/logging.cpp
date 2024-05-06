#include "logging.hpp"

#include <fstream>
#include <iostream>

#include "string/kus_string.hpp"

//------------------------------------------------------------------------------

void
core::Logging::setLogLevel(core::Logging::LogLevel aOutputType) noexcept
{
    getInstance().mLogLevel = aOutputType;
}

void
core::Logging::setOutputType(core::Logging::OutputType aOutputType,
                             const str::string& aFileName) noexcept
{
    getInstance().setOutputTypeNonstatic(aOutputType, aFileName);
}

void
core::Logging::setOutputTypeNonstatic(core::Logging::OutputType aOutputType,
                                      const str::string& aFileName) noexcept
{
    if (aOutputType == OutputType::File && aFileName.empty())
    {
        LOG_ERROR("The name of the log buffer file is not specified, \
            no changes are applied");
        return;
    }

    clear();
    switch (aOutputType)
    {
        case OutputType::Cout:
            mStream = stdout;
            LOG_INFO("Log buffer changed to stdout");
            break;
        case OutputType::Cerr:
            mStream = stderr;
            LOG_INFO("Log buffer changed to stderr");
            break;
        case OutputType::File:
            mStream       = std::fopen(aFileName.c_str(), "w");
            mIsFileOutput = true;
            LOG_INFO("Log buffer changed to ", aFileName, " file");
            break;
        default:
            mStream = stdout;
            LOG_INFO("Log buffer changed to default (cout)");
            break;
    }
}

//------------------------------------------------------------------------------

core::Logging::Logging() noexcept
{
    mIsFileOutput = false;
    mLogLevel     = LogLevel::Info;
    mStream       = stdout;
}

core::Logging::~Logging()
{
    clear();
}

void
core::Logging::clear() noexcept
{
    if (mIsFileOutput)
    {
        // TODO: do we need close?
        delete mStream;
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

// TODO: centrate
// printf("%*s%*s\n",10+strlen(s)/2,s,10-strlen(s)/2,"");

void
core::Logging::writeDebugData(const char* arg, int aMaxSize) noexcept
{
    std::fprintf(mStream, "[%-*s] ", aMaxSize, arg);
}

void
core::Logging::writeDebugData(int arg, int aMaxSize) noexcept
{
    std::fprintf(mStream, "[%-*d] ", aMaxSize, arg);
}

void
core::Logging::writeFileName(const char* arg, int aMaxSize) noexcept
{
    int num = strlen(arg);
    int cnt = 0;
    while (num > 0 && cnt < 2)
    {
        if (arg[num] == '/' || arg[num] == '\\')
        {
            ++cnt;
        }
        --num;
    }
    std::fprintf(mStream, "[%-*s] ", aMaxSize, arg + num + 1);
}

void
core::Logging::writeArg(int arg) noexcept
{
    std::fprintf(mStream, "%d ", arg);
}

void
core::Logging::writeArg(const str::string& arg) noexcept
{
    std::fprintf(mStream, "%s ", arg.c_str());
}

void
core::Logging::writeArg(const char* arg) noexcept
{
    std::fprintf(mStream, "%s ", arg);
}

void
core::Logging::writeEnd() noexcept
{
    std::fprintf(mStream, "\n");
}
