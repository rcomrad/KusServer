#pragma once

//--------------------------------------------------------------------------------

#include <cstdio>
#include <string>

#include "kernel/utility/type/concepts.hpp"

//--------------------------------------------------------------------------------

namespace util
{

class FileWrite
{
public:
    FileWrite(const std::string& a_file_name);
    ~FileWrite();

    template <MapedContainer T>
    void write(const T& a_container)
    {
        for (auto& i : a_container)
        {
            fprintf(m_file, "%s\n", i.second.toString().c_str());
        }
        std::fflush(m_file);
    }

private:
    FILE* m_file;
};

} // namespace util

//--------------------------------------------------------------------------------
