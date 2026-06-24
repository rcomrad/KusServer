#include "file_system.hpp"

namespace core
{

std::string
FileSystem::readFile(const std::string& a_name,
                     const std::filesystem::path& a_path_postfix) const
{
    auto path = getShortcut(a_name, a_path_postfix);
    return FileReader::readFile(path);
}

std::string
FileSystem::readBinaryFile(const std::string& a_name,
                           const std::filesystem::path& a_path_postfix) const
{
    auto path = getShortcut(a_name, a_path_postfix);
    return FileReader::readBinaryFile(path);
}

std::string
FileSystem::readFileFromDir(const std::string& a_name,
                            const std::string& a_dir_name) const
{
    auto base_path = getShortcut(a_dir_name);
    auto path      = base_path / a_name;
    return FileReader::readFile(path);
}

void
FileSystem::writeFile(const std::string& a_data,
                      const std::string& a_name,
                      const std::filesystem::path& a_path_postfix) const
{
    auto path = getShortcut(a_name, a_path_postfix);
    return FileWriter::writeFile(path, a_data);
}

} // namespace core
