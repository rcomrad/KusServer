#include "file_write.hpp"

#include <cstdio>

#include "core/logging/logging.hpp"

#include "path_storage.hpp"

util::FileWrite::FileWrite(const core::Context& a_context,
                           const str::string& a_file_name) noexcept
    : m_is_print_error_msg(false)
{
    GET_FILE_PATH(file_path, a_file_name, &a_context);
    m_file = std::fopen(file_path.data(), "w");
    if (!m_file)
    {
        CONTEXT_ERROR(a_context,
                      "Can't open file for write. Name: '%s', path: '%s'.",
                      a_file_name, file_path);
    }
}

util::FileWrite::~FileWrite() noexcept
{
    if (m_file != nullptr)
    {
        std::fclose(m_file);
    }
}

void
util::FileWrite::write(const char* format, ...) noexcept
{
    if (m_file == nullptr)
    {
        if (!m_is_print_error_msg)
        {
            m_is_print_error_msg = true;
            LOG_ERROR("Unable to write in broken file.");
        }
        return;
    }

    va_list args;
    va_start(args, format);
    vfprintf(m_file, format, args);
    va_end(args);
}
