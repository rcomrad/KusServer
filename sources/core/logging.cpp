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
            mStreams = &std::cout;
            writeInfo("Log buffer changed to stdout");
            break;
        case OutputType::Cerr:
            mStreams = &std::cerr;
            writeInfo("Log buffer changed to stderr");
            break;
        case OutputType::File:
            mStreams      = new std::ofstream(aFileName);
            mIsFileOutput = true;
            writeInfo("Log buffer changed to ", aFileName, " file");
            break;
        default:
            mStreams = &std::cout;
            writeInfo("Log buffer changed to default (cout)");
            break;
    }
}

//------------------------------------------------------------------------------

core::Logging::Logging() noexcept
{
    mIsFileOutput = false;
    mLogLevel     = LogLevel::Info;
    mStreams      = &std::cout;
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
        delete mStreams;
        mIsFileOutput = false;
    }
}

core::Logging&
core::Logging::getInstance() noexcept
{
    static Logging instance;
    return instance;
}
