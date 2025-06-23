#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "level.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Logger
{
public:
    Logger() noexcept;
    ~Logger();

    void redirect(const std::string& a_name) noexcept;
    void redirectDefault(const std::string& a_name) noexcept;

    void pushTeeBuffer(std::unique_ptr<char[]>& a_buffer) noexcept;
    void popTeeBuffer() noexcept;

    void writeLog(LogLevel a_level, const char* a_format, ...) noexcept;
    void teeLog(LogLevel a_level, const char* a_format, ...) noexcept;

private:
    static FILE* default_stream;
    static std::mutex default_mutex;

    bool m_is_shared;
    FILE* m_stream;
    std::vector<std::unique_ptr<char[]>*> m_tee_buffers;

    void redirectImpl(const std::string& a_name, FILE** s_stream) noexcept;
};

} // namespace core
