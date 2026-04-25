#include "file_writer.hpp"

#include <fstream>
#include <iostream>

#include "kernel/framework/logger/include_me.hpp"

namespace core
{

void
FileWriter::writeFile(const std::filesystem::path& a_path,
                      const std::string& a_data) const
{
    std::ofstream out(a_path);
    if (!out)
    {
        THROW("Can't open file for write with path: '%s'", a_path.string());
    }
    out << a_data;
}

} // namespace core
