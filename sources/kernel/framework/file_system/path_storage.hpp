#pragma once

//------------------------------------------------------------------------------

#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//------------------------------------------------------------------------------

namespace core
{

class PathStorage
{
public:
    PathStorage();

    const std::filesystem::path& addDataShortcut(
        const std::string& a_name,
        const std::filesystem::path& a_path);

    std::filesystem::path getShortcut(
        const std::string& a_name,
        const std::filesystem::path& a_path_postfix = {}) const;

    std::vector<std::filesystem::path> getShortcutFileContent(
        const std::string& a_name) const;

private:
    std::unordered_set<std::filesystem::path> m_used_paths;
    std::unordered_map<std::string, std::filesystem::path> m_path_shortcuts;

    const std::filesystem::path& addShortcut(
        const std::string& a_name,
        const std::filesystem::path& a_path);

    void touchFolder(const std::filesystem::path& a_path);
};

} // namespace core

//------------------------------------------------------------------------------
