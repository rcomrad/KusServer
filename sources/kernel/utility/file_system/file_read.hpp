#pragma once

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace util
{

class FileRead
{
public:
    FileRead() = delete;

    static std::string read(const std::string& a_file_name);
};

} // namespace util

//--------------------------------------------------------------------------------
