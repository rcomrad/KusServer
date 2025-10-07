#include "logger.hpp"

#include <cstdarg>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/utility/file_system/path_values.hpp"

#include "level.hpp"

//------------------------------------------------------------------------------

namespace
{

constexpr const char* LOGS_FOLDER_NAME    = "logs";
constexpr const char* LOGS_FILE_EXTENSION = "log";

} // namespace

FILE* core::Logger::default_stream = stdout;
std::mutex core::Logger::default_mutex;

//------------------------------------------------------------------------------

core::Logger::Logger() noexcept : m_stream(default_stream), m_is_shared(true)
{
    m_tee_buffers.reserve(2);
}

core::Logger::~Logger()
{
    if (m_stream != default_stream)
    {
        std::fclose(m_stream);
    }
}

//------------------------------------------------------------------------------

void
core::Logger::redirect(const std::string& a_name) noexcept
{
    if (m_stream != default_stream)
    {
        std::fclose(m_stream);
    }
    m_is_shared = false;
    redirectImpl(a_name, &m_stream);
}

void
core::Logger::redirectDefault(const std::string& a_name) noexcept
{
    static bool flag = false;
    if (!flag)
    {
        // std::fclose(default_stream);
        redirectImpl(a_name, &default_stream);
        flag = true;
    }
}

void
core::Logger::redirectImpl(const std::string& a_name, FILE** s_stream) noexcept
{
    KERNEL.addFolder(util::DATA_FOLDER_NAME, LOGS_FOLDER_NAME);

    std::string log_file_name(a_name);
    log_file_name.push_back('.');
    log_file_name += LOGS_FILE_EXTENSION;

    auto& path = KERNEL.addFile(LOGS_FOLDER_NAME, log_file_name);
    *s_stream  = std::fopen(path.c_str(), "w");
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
core::Logger::writeLog(LogLevel a_level, const char* a_format, ...) noexcept
{
    if (a_level >= g_log_level)
    {
        if (m_is_shared) default_mutex.lock();
        va_list args;
        va_start(args, a_format);
        vfprintf(m_stream, a_format, args);
        va_end(args);
        fflush(m_stream);
        if (m_is_shared) default_mutex.unlock();
    }
}

void
core::Logger::teeLog(LogLevel a_level, const char* a_format, ...) noexcept
{
    if (a_level >= LogLevel::ERROR || a_level == LogLevel::CMD)
    {
        while (!m_tee_buffers.empty())
        {
            auto& buffer = *m_tee_buffers.back();
            popTeeBuffer();

            va_list args_count;
            va_start(args_count, a_format);
            int count = vsnprintf(nullptr, 0, a_format, args_count);
            va_end(args_count);

            buffer = std::make_unique<char[]>(count + 1);

            va_list args_print;
            va_start(args_print, a_format);
            vsprintf(buffer.get(), a_format, args_print);
            va_end(args_print);
        }
    }
}

//------------------------------------------------------------------------------
