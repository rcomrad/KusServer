#pragma once

//------------------------------------------------------------------------------

#include <filesystem>
#include <string>

//------------------------------------------------------------------------------

namespace core
{

class FileWriter
{
public:
    void writeFile(const std::filesystem::path& a_path,
                   const std::string& a_data) const;
};

/*
    template <MapedContainer T>
    void write(const T& a_container)
    {
        for (auto& i : a_container)
        {
            fprintf(m_file, "%s\n", i.second.toString().c_str());
        }
        std::fflush(m_file);
    }


utils::FileWrite::FileWrite(const std::string& a_file_name)
{
    auto& file_path = KERNEL.getFilePath(a_file_name);
    m_file          = std::fopen(file_path.data(), "w");
    if (!m_file)
    {
        THROW("Can't open file for write. Name: '%s', path: '%s'.", a_file_name,
              file_path);
    }
}


*/

} // namespace core

//------------------------------------------------------------------------------
