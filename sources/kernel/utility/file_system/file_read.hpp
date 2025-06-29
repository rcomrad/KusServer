#pragma once

//--------------------------------------------------------------------------------

#include <cstdio>
#include <string>

//--------------------------------------------------------------------------------

namespace util
{

class FileRead
{
public:
    FileWrite() = delete;
    ~FileWrite();

    
const std::string& a_file_name


    template <typename T>
    void write(const T& a_container)
    {
        for (auto& i : a_container)
        {
            fprintf(m_file, "%s\n", i.to_string());
        }
        std::flush(m_file);
    }

private:
    FILE* m_file;
};

} // namespace util

//--------------------------------------------------------------------------------
