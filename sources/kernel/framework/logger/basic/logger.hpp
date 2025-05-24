#pragma once

#include <memory>
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

    void init(const std::string& a_name) noexcept;

    void pushTeeBuffer(std::unique_ptr<char[]>& a_buffer) noexcept;
    void popTeeBuffer() noexcept;

    void writeLog(LogLevel a_level, const char* a_format, ...) noexcept;
    void teeLog(LogLevel a_level, const char* a_format, ...) noexcept;

private:
    FILE* m_stream;
    std::vector<std::unique_ptr<char[]>*> m_tee_buffers;
};

} // namespace core
