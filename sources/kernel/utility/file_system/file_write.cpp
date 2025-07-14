#include "file_write.hpp"

#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/include_me.hpp"

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
