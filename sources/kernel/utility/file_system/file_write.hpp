#pragma once

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace util
{

class FileWrite
{
public:
    FileWrite(const std::string& a_file_name);
    ~FileWrite();

    void write(const char* format, ...) noexcept;

private:
    FILE* m_file;
};

} // namespace util

//--------------------------------------------------------------------------------
