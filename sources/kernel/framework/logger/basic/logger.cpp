#include "logger.hpp"

#include <cstdarg>

#include "kernel/framework/module/kernel.hpp"
#include "kernel/utility/file_system/path_values.hpp"

#include "level.hpp"

//------------------------------------------------------------------------------

namespace
{

constexpr const char* LOGS_FOLDER_NAME    = "logs";
constexpr const char* LOGS_FILE_EXTENSION = "log";

} // namespace

//------------------------------------------------------------------------------

core::Logger::Logger() noexcept : m_stream(nullptr)
{
    m_tee_buffers.reserve(2);
}

core::Logger::~Logger()
{
    fflush(m_stream);
    std::fclose(m_stream);
}

void
core::Logger::init(const std::string& a_name) noexcept
{
    KERNEL.addFolder(util::DATA_FOLDER_NAME, LOGS_FOLDER_NAME);

    std::string log_file_name(a_name);
    log_file_name.push_back('.');
    log_file_name += LOGS_FILE_EXTENSION;

    auto& path = KERNEL.addFile(LOGS_FOLDER_NAME, log_file_name);
    m_stream   = std::fopen(path.c_str(), "w");
}

//------------------------------------------------------------------------------

void
core::Logger::pushTeeBuffer(std::unique_ptr<char[]>& a_buffer) noexcept
{
    m_tee_buffers.push_back(&a_buffer);
}

void
core::Logger::popTeeBuffer() noexcept
{
    if (!m_tee_buffers.empty())
    {
        m_tee_buffers.pop_back();
    }
}

//------------------------------------------------------------------------------

void
core::Logger::writeLog(LogLevel a_level, const char* format, ...) noexcept
{
    if (a_level >= g_log_level)
    {
        va_list args;
        va_start(args, format);
        vfprintf(m_stream, format, args);
        va_end(args);
        fflush(m_stream);
    }

    if (a_level >= LogLevel::ERROR || a_level == LogLevel::CMD)
    {
        while (!m_tee_buffers.empty())
        {
            auto& buffer = *m_tee_buffers.back();
            popTeeBuffer();

            va_list args_count;
            va_start(args_count, format);
            int count = vsnprintf(nullptr, 0, format, args_count);
            va_end(args_count);

            buffer = std::make_unique<char[]>(count + 1);

            va_list args_print;
            va_start(args_print, format);
            vsprintf(buffer.get(), format, args_print);
            va_end(args_print);
        }
    }
}

//------------------------------------------------------------------------------
