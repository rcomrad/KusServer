#include "file_write.hpp"

#include <cstdio>
#include <stdarg.h>

#include "kernel/framework/logger/include_me.hpp"
#include "kernel/framework/module/kernel.hpp"

util::FileWrite::FileWrite(const std::string& a_file_name)
{
    auto& file_path = KERNEL.getFilePath(a_file_name);
    m_file          = std::fopen(file_path.data(), "w");
    if (!m_file)
    {
        THROW("Can't open file for write. Name: '%s', path: '%s'.", a_file_name,
              file_path);
    }
}

util::FileWrite::~FileWrite()
{
    if (m_file != nullptr)
    {
        std::fclose(m_file);
    }
}

void
util::FileWrite::write(const char* format, ...) noexcept
{
    va_list args;
    va_start(args, format);
    vfprintf(m_file, format, args);
    va_end(args);
}
