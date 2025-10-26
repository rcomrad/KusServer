#pragma once

//------------------------------------------------------------------------------

#include "kernel/utility/type/concepts.hpp"

#include "file_reader.hpp"
#include "file_writer.hpp"
#include "path_storage.hpp"

//------------------------------------------------------------------------------

namespace core
{

class FileSystem : public PathStorage, public FileReader, public FileWriter
{
    template <typename T>
    std::string toString(const T& a_container) const
    {
        std::string result;
        for (auto& i : a_container)
        {
            result += i.second.toString();
            result += "\n";
        }
        return result;
    }

public:
    std::string readFile(
        const std::string& a_name,
        const std::filesystem::path& a_path_postfix = {}) const;
    std::string readBinaryFile(
        const std::string& a_name,
        const std::filesystem::path& a_path_postfix = {}) const;

    template <utils::IsNotStdString T>
    void writeFile(const T a_data,
                   const std::string& a_name,
                   const std::filesystem::path& a_path_postfix = {}) const
    {
        writeFile(toString(a_data), a_name, a_path_postfix);
    }
    void writeFile(const std::string& a_data,
                   const std::string& a_name,
                   const std::filesystem::path& a_path_postfix = {}) const;
};

} // namespace core

//------------------------------------------------------------------------------
