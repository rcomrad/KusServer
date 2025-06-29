#include "file_read.hpp"

#include <fstream>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/include_me.hpp"

std::string
util::FileRead::read(const std::string& a_file_name)
{
    auto& file_path = KERNEL.getFilePath(a_file_name);
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        THROW("Can't open file for write. Name: '%s', path: '%s'.", a_file_name,
              file_path);
    }

    std::string result;
    std::getline(file, result, '\0');
    return result;
}
