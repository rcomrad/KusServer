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
    std::string readFile(const std::filesystem::path& a_path) const;
    std::string readBinaryFile(const std::filesystem::path& a_path) const;

private:
    std::string readFileImpl(std::ifstream& a_inp) const;
};

} // namespace core

//------------------------------------------------------------------------------
