#include "path_storage.hpp"

#include "kernel/framework/logger/include_me.hpp"

#include "base_shortcut.hpp"

namespace core
{

PathStorage::PathStorage()
{
    auto bin_path = std::filesystem::current_path();
    auto app_path = bin_path.parent_path();

    addShortcut(BIN_DIR, bin_path);
    addShortcut(APP_DIR, app_path);
    addShortcut(DATA_DIR, app_path / DATA_DIR);
    addShortcut(LOG_DIR, app_path / DATA_DIR / LOG_DIR);
}

const std::filesystem::path&
PathStorage::addShortcut(const std::string& a_name,
                         const std::filesystem::path& a_path)
{
    if (m_path_shortcuts.count(a_name))
    {
        THROW("Shortcut with name %s already exist", a_name);
    }

    if (m_used_paths.count(a_path))
    {
        THROW("Shortcut with path %s already exist", a_path.string());
    }

    touchFolder(a_path);
    m_used_paths.emplace(a_path);
    return m_path_shortcuts.emplace(std::move(a_name), a_path).first->second;
}

std::filesystem::path
PathStorage::getShortcut(const std::string& a_name,
                         const std::filesystem::path& a_path_postfix) const
{
    auto it = m_path_shortcuts.find(a_name);
    if (it == m_path_shortcuts.end())
    {
        THROW("There are NO shortcut with name %s", a_name);
    }

    auto result = it->second;
    if (!a_path_postfix.empty())
    {
        result /= a_path_postfix;
    }
    return result;
}

std::vector<std::filesystem::path>
PathStorage::getShortcutFileContent(const std::string& a_name) const
{
    std::vector<std::filesystem::path> result;

    auto path = getShortcut(a_name);
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (std::filesystem::is_regular_file(entry.status()))
        {
            result.emplace_back(entry.path());
        }
    }

    return result;
}

const std::filesystem::path&
PathStorage::addDataShortcut(const std::string& a_name,
                             const std::filesystem::path& a_path)
{
    return addShortcut(a_name, getShortcut(DATA_DIR, a_path));
}

void
PathStorage::touchFolder(const std::filesystem::path& a_path)
{
    auto path = a_path;
    path.remove_filename();
    std::filesystem::create_directories(path);
}

} // namespace core
