#include "logging.hpp"

#include <cstring>

SINGLETON_DEFINITOR(core, Logging);

//------------------------------------------------------------------------------

void
core::Logging::setLogLevel(core::Logging::LogLevel aOutputType) noexcept
{
    getInstance().mLogLevel = aOutputType;
}

void
core::Logging::setOutputTypeNonstatic(core::Logging::OutputType aOutputType,
                                      const str::string& aFileName) noexcept
{
    if (aOutputType == OutputType::FILE && aFileName.empty())
    {
        LOG_ERROR("The name of the log buffer file is not specified, no "
                  "changes are applied");
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
            mStream       = std::fopen(aFileName.c_str(), "w");
            mIsFileOutput = true;
            LOG_INFO("Log buffer changed to '%s' file", aFileName);
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
