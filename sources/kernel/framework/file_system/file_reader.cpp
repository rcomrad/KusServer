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
    std::ifstream inp(a_path);
    if (!inp)
    {
        THROW("Can't open file for read with path: '%s'", a_path.string());
    }
    return readFileImpl(inp);
}

std::string
FileReader::readBinaryFile(const std::filesystem::path& a_path)
{
    std::ifstream inp(a_path, std::ios::binary);
    if (!inp)
    {
        THROW("Can't open file for read with path: '%s'", a_path.string());
    }
    return readFileImpl(inp);
}

std::string
FileReader::readFileImpl(std::ifstream& a_inp)
{
    std::stringstream buffer;
    buffer << a_inp.rdbuf();
    return buffer.str();
}

} // namespace core
