#include "printer.hpp"

#include <iostream>

#include "kernel/framework/module/base.hpp"
#include "kernel/utility/file_system/path_values.hpp"

#include "logging.hpp"

//------------------------------------------------------------------------------

namespace
{

constexpr const char* LOGS_FILE_NAME = "logs.txt";

}

//------------------------------------------------------------------------------

core::Printer::Printer() noexcept
    : m_is_file_output(false), m_log_level(LogLevel::INFO), m_stream(stdout)
{
}

core::Printer::~Printer()
{
    clear();
}

void
core::Printer::init()
{
    registrateBaseCommand("set_log_mode", "Sets logging level.",
                          "info|warn|err");
    registrateBaseCommand("set_log_type", "Sets stream for logs recording.",
                          "stdout|stderr|file <file_name>");

    auto& file_name = KERNEL.addFile(util::DATA_FOLDER_NAME, LOGS_FILE_NAME);
    setOutputType(OutputType::FILE, file_name);
}

void
core::Printer::clear() noexcept
{
    fflush(m_stream);
    if (m_is_file_output && m_stream != nullptr)
    {
        std::fclose(m_stream);
        m_stream         = nullptr;
        m_is_file_output = false;
    }
}

//------------------------------------------------------------------------------

// void
// print(FILE* a_buff, const char* a_format, ...)
// {
//     va_list args;
//     va_start(args, format);
//     vfprintf(a_buff, format, args);
//     va_end(args);
//     if (a_level == LogLevel::ERROR)
//     {
//         fflush(m_stream);
//     }
// }

void
core::Printer::writeLog(LogLevel a_level,
                        std::unique_ptr<char[]>* tee_buff,
                        const char* format,
                        ...)
{
    if (a_level < m_log_level)
    {
        return;
    }

    std::unique_lock lock(m_write_mutex);

    va_list args;
    va_start(args, format);
    vfprintf(m_stream, format, args);
    va_end(args);
    // if (a_level == LogLevel::ERROR) // TODO: fix, file not working!
    {
        fflush(m_stream);
    }

    lock.unlock();

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
core::Printer::setLogLevel(core::Printer::LogLevel a_output_type) noexcept
{
    m_log_level = a_output_type;
}

void
core::Printer::setOutputType(core::Printer::OutputType a_output_type,
                             const std::string& a_file_name)
{
    if (a_output_type == OutputType::FILE && a_file_name.empty())
    {
        LOG_ERROR("The name of the log buffer file is not specified, no "
                  "changes are applied");
        return;
    }

    clear();
    switch (a_output_type)
    {
        case OutputType::STDOUT:
            m_stream = stdout;
            LOG_INFO("Log buffer changed to stdout");
            break;
        case OutputType::STDERR:
            m_stream = stderr;
            LOG_INFO("Log buffer changed to stderr");
            break;
        case OutputType::FILE:
            m_stream         = std::fopen(a_file_name.c_str(), "w");
            m_is_file_output = true;
            LOG_INFO("Log buffer changed to '%s' file", a_file_name);
            break;
        default:
            if (m_stream == nullptr)
            {
                m_stream = stdout;
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

void
core::Printer::setLogLevel(core::Command& a_command)
{
    CMD_ASSERT(noVars().argCount(1));

    // TODO: str ->enum
    auto& mode     = a_command.arguments[0];
    LogLevel level = m_log_level;

    if (mode == "info")
    {
        level = LogLevel::INFO;
    }
    else if (mode == "warn")
    {
        level = LogLevel::WARN;
    }
    else if (mode == "error")
    {
        level = LogLevel::ERROR;
    }

    setLogLevel(level);
}

void
core::Printer::setLogType(core::Command& a_command)
{
    CMD_ASSERT(noVars().argCount({1, 2}));
}

//------------------------------------------------------------------------------
