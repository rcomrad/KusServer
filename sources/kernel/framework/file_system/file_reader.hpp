#pragma once

//------------------------------------------------------------------------------

#include <filesystem>
#include <fstream>
#include <string>

//------------------------------------------------------------------------------

namespace core
{

class FileReader
{
public:
    static std::string readFile(const std::filesystem::path& a_path);
    static std::string readBinaryFile(const std::filesystem::path& a_path);

private:
    static std::string readFileImpl(std::ifstream& a_inp);
};

} // namespace core

//------------------------------------------------------------------------------
