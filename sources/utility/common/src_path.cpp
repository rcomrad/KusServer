#include "src_path.hpp"

#include <filesystem>
#include <unordered_map>

#define FILE_PATH_ADDR reinterpret_cast<size_t>(a_file_path)

const char*
util::getSourceFolderNameChr(const char* a_file_path) noexcept
{
    return getSourceFolderNameStr(a_file_path).c_str();
}

const std::string&
util::getSourceFolderNameStr(const char* a_file_path) noexcept
{
    static std::unordered_map<size_t, std::string> m_folder_paths;
    auto it = m_folder_paths.find(FILE_PATH_ADDR);
    if (it == m_folder_paths.end())
    {
        std::filesystem::path path(a_file_path);
        path.remove_filename();
        auto& addr = m_folder_paths[FILE_PATH_ADDR] = path.string();
        it = m_folder_paths.find(FILE_PATH_ADDR);
    }
    return it->second;
}
