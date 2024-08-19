#include "printer.hpp"

#include <iostream>

#include "logging.hpp"

SINGLETON_DEFINITOR(core, Printer);

//------------------------------------------------------------------------------

void
core::Printer::setLogLevel(core::LogLevel aOutputType) noexcept
{
    getInstance().mLogLevel = aOutputType;
}

//------------------------------------------------------------------------------

void
core::Printer::write(LogLevel a_level,
                     std::unique_ptr<char[]>* tee_buff,
                     const char* format,
                     ...)
{
    if (a_level < mLogLevel)
    {
        return;
    }

    {
        const std::lock_guard lock(m_write_mutex);

        va_list args;
        va_start(args, format);
        vfprintf(mStream, format, args);
        va_end(args);
        if (a_level == LogLevel::ERROR)
        {
            fflush(mStream);
        }
    }

    if (tee_buff)
    {
        va_list args_count;
        va_start(args_count, format);
        int count = vsnprintf(nullptr, 0, format, args_count);
        va_end(args_count);

        *tee_buff = std::make_unique<char[]>(count + 1);

        va_list args_print;
        va_start(args_print, format);
        vsprintf(tee_buff->get(), format, args_print);
        va_end(args_print);
    }
}

//------------------------------------------------------------------------------

void
core::Printer::setOutputTypeNonstatic(core::Printer::OutputType aOutputType,
                                      const std::string& aFileName) noexcept
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

core::Printer::Printer() noexcept
{
    mIsFileOutput = false;
    mLogLevel     = LogLevel::INFO;
    mStream       = stdout;
}

core::Printer::~Printer()
{
    clear();
}

void
core::Printer::clear() noexcept
{
    fflush(mStream);
    if (mIsFileOutput && mStream != nullptr)
    {
        std::fclose(mStream);
        mStream       = nullptr;
        mIsFileOutput = false;
    }
}
