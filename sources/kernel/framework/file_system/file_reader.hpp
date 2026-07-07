#pragma once

//------------------------------------------------------------------------------

#include <filesystem>
#include <fstream>
#include <string>

#include "struct_reader.hpp"

//------------------------------------------------------------------------------

namespace core
{

class FileReader : public StructReader
{
public:
    static std::string readFile(const std::filesystem::path& a_path);
    static std::string readBinaryFile(const std::filesystem::path& a_path);

    template <typename T>
    static std::unordered_map<std::string, T> readStructMap(
        const std::filesystem::path& a_path)
    {
        return readMap<T>(open(a_path));
    }

private:
    static std::ifstream open(
        const std::filesystem::path& a_path,
        std::ios_base::openmode a_mode = std::ios_base::in);
    static std::string readFileImpl(std::ifstream&& a_inp);
};

} // namespace core

//------------------------------------------------------------------------------
