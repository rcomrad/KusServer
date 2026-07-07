#include "file_reader.hpp"

#include "kernel/framework/logger/include_me.hpp"

#include <iostream>
#include <sstream>

namespace core
{

// TODO: template?

std::string
FileReader::readFile(const std::filesystem::path& a_path)
{
    return readFileImpl(open(a_path));
}

std::string
FileReader::readBinaryFile(const std::filesystem::path& a_path)
{
    return readFileImpl(open(a_path, std::ios::binary));
}

std::ifstream
FileReader::open(const std::filesystem::path& a_path,
                 std::ios_base::openmode a_mode)
{
    std::ifstream result(a_path, a_mode);
    if (!result)
    {
        THROW("Can't open file for read with path: '%s'", a_path.string());
    }
    return result;
}

std::string
FileReader::readFileImpl(std::ifstream&& a_inp)
{
    std::stringstream buffer;
    buffer << a_inp.rdbuf();
    return buffer.str();
}

} // namespace core
