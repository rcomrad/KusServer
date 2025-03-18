#include "path_storage.hpp"

#include <filesystem>

#include "core/logging/logging.hpp"

#include "path_values.hpp"

//------------------------------------------------------------------------------
// Path storage initialization
//------------------------------------------------------------------------------

SINGLETON_DEFINITOR(util, PathStorage);

#define SCOPED_CONTEXT(command, ...)          \
    {                                         \
        DECLARE_LOCAL_CONTEXT;                \
        command(__VA_ARGS__, &context_local); \
    }

util::PathStorage::PathStorage() noexcept
{
    // Set path to bin and its parant folders
    auto bin_path = std::filesystem::current_path();

    // SCOPED_CONTEXT(addFolderNonstatic, BIN_PATH_NAME,
    //                util::Path::normalizeSeparators(bin_path.string()));

    auto app_folder_path_str = bin_path.parent_path().string();

    SCOPED_CONTEXT(addFolderNonstatic, APP_PATH_NAME,
                   util::Path::normalizeSeparators(app_folder_path_str));

    addContentToPathsNonstatic(app_folder_path_str, ObjectType::FOLDER,
                               LevelType::CURRENT);

    SCOPED_CONTEXT(touchFolderNonstatic,
                   Path::combine(true, app_folder_path_str, DATA_FOLDER_NAME));
}

//------------------------------------------------------------------------------
// Adding paths to the storage
//------------------------------------------------------------------------------

std::optional<std::string_view>
util::PathStorage::addFileNonstatic(std::string_view a_folder_name,
                                    std::string_view a_file_name,
                                    const core::Context* a_context) noexcept
{
    std::optional<std::string_view> result;
    auto folder_path = getFolderPath(a_folder_name);
    if (folder_path.has_value())
    {
        addObject(m_files_paths, a_file_name,
                  Path::combine(false, folder_path.value(), a_file_name),
                  a_context, false);
    }
    else
    {
        if (a_context)
        {
            CONTEXT_ERROR((*a_context),
                          "Unable to add %s file to path storage: "
                          "folder with named '%s' doesn't exists.",
                          a_file_name, a_folder_name);
        }
    }
    return result;
}

std::optional<std::string_view>
util::PathStorage::addFileNonstatic(std::string_view a_file_path,
                                    const core::Context* a_context) noexcept
{
    return addObject(m_files_paths, Path::getName(a_file_path, *a_context),
                     a_file_path, a_context, false);
}

std::optional<std::string_view>
util::PathStorage::addFolderNonstatic(std::string_view a_folder_name,
                                      std::string_view a_folder_path,
                                      const core::Context* a_context) noexcept
{
    return addObject(m_folder_paths, a_folder_name,
                     Path::normalizeFolderPath(a_folder_path, true), a_context,
                     true);
}

std::optional<std::string_view>
util::PathStorage::addFolderNonstatic(std::string_view a_folder_path,
                                      const core::Context* a_context) noexcept
{
    return addObject(m_folder_paths, Path::getName(a_folder_path, *a_context),
                     Path::normalizeFolderPath(a_folder_path, true), a_context,
                     true);
}

std::optional<std::string_view>
util::PathStorage::addObject(
    std::unordered_map<std::string_view, std::string>& a_storage,
    std::string_view a_name,
    std::string_view a_path,
    const core::Context* a_context,
    bool a_is_folder) noexcept
{
    // TODO: string_view map
    std::optional<std::string_view> result;
    auto it = a_storage.find(a_name);
    if (it == a_storage.end())
    {
        auto& new_element_it =
            *m_str_storage
                 .insert(a_is_folder ? Path::normalizeFolderPath(a_name, false)
                                     : std::string(a_name))
                 .first;
        a_storage[new_element_it] = a_path;
        result                    = a_storage[new_element_it];
    }
    else if (a_context)
    {
        CONTEXT_ERROR((*a_context),
                      "Unable to add %s to path storage: "
                      "an object named '%s' already exists.",
                      a_is_folder ? "folder" : "file", a_name);
    }
    return result;
}

//--------------------------------------------------------------------------------
// Search for a path of an object in storage
//--------------------------------------------------------------------------------

std::optional<std::string_view>
util::PathStorage::getFilePathNonstatic(std::string_view a_file_name,
                                        const core::Context* a_context) noexcept
{
    return searchInStorage(m_files_paths, a_file_name, a_context, "file");
}

std::optional<std::string>
util::PathStorage::getFilePathNonstatic(std::string_view a_folder_name,
                                        std::string_view a_file_name,
                                        const core::Context* a_context) noexcept
{
    auto path = getFolderPathNonstatic(a_folder_name);
    std::string result;
    if (path.has_value())
    {
        result = Path::combine(false, path.value(), a_file_name);
    }
    return result;
}

std::optional<std::string_view>
util::PathStorage::getFolderPathNonstatic(
    std::string_view a_folder_name,
    const core::Context* a_context) noexcept
{
    return searchInStorage(m_folder_paths, a_folder_name, a_context, "folder");
}

std::optional<std::string_view>
util::PathStorage::searchInStorage(
    std::unordered_map<std::string_view, std::string>& a_storage,
    const std::string_view& a_key,
    const core::Context* a_context,
    const char* a_msg) noexcept
{
    std::optional<std::string_view> result;
    auto it = a_storage.find(a_key);
    if (it != a_storage.end())
    {
        result = it->second;
    }
    else if (a_context)
    {
        CONTEXT_ERROR((*a_context), "There is no '%s' %s in path storage.",
                      a_key, a_msg);
    }
    return result;
}

//--------------------------------------------------------------------------------
// Folder manipulation
//--------------------------------------------------------------------------------

std::optional<std::string_view>
util::PathStorage::touchFolderNonstatic(std::string_view a_folder_name,
                                        std::string_view a_parent_path,
                                        const core::Context* a_context) noexcept
{
    return touchFolderImpl(a_folder_name,
                           Path::combine(true, a_parent_path, a_folder_name),
                           a_context);
}

std::optional<std::string_view>
util::PathStorage::touchFolderNonstatic(std::string_view a_full_path,
                                        const core::Context* a_context) noexcept
{
    return touchFolderImpl(Path::getName(a_full_path, *a_context), a_full_path,
                           a_context);
}

std::optional<std::string_view>
util::PathStorage::touchFolderImpl(
    std::string_view a_folder_name,
    std::string_view a_full_path,
    const core::Context* a_context = nullptr) noexcept
{
    std::optional<std::string_view> result;

    auto stored_folder_opt = getFolderPathNonstatic(a_folder_name);
    if (stored_folder_opt.has_value())
    {
        auto& stored_path = stored_folder_opt.value();
        bool flag         = a_full_path == stored_path;
        if (flag)
        {
            result = stored_path;
        }
        else if (a_context)
        {
            CONTEXT_ERROR((*a_context),
                          "Touched folder already exists in path storage. "
                          "Name: '%s', cur_path: '%s', new_path '%s'.",
                          a_folder_name, stored_path, a_full_path);
        }
    }
    else
    {
        CONTEXT_INFO((*a_context), "Create folder with name: '%s', path '%s'.",
                     a_folder_name, a_full_path);
        result = addObject(m_folder_paths, a_folder_name, a_full_path,
                           a_context, "folder");
        LOG_CATCH(std::filesystem::create_directories(a_full_path),
                  (*a_context),
                  "Unable to create folder, name: '%s', path: '%s'.",
                  a_folder_name, a_full_path);
    }

    return result;
}

bool
util::PathStorage::removeFolderNonstatic(
    std::string_view a_folder_name,
    const core::Context& a_context) noexcept
{
    bool result = false;

    auto folderPath = getFolderPathNonstatic(a_folder_name);
    if (folderPath.has_value())
    {
        auto& folder_path = folderPath.value();
        m_folder_paths.erase(a_folder_name);
        LOG_CATCH(result = std::filesystem::remove_all(folder_path), a_context,
                  "Failed to delete folder, name: '%s', path: '%s'.",
                  a_folder_name, folder_path);
        if (result)
        {
            CONTEXT_INFO(a_context, "Delete folder named '%s'.", folder_path);
        }
        else
        {
            CONTEXT_ERROR(a_context,
                          "Unexpected error when deleting a folder '%s'.",
                          folder_path);
        }
    }
    else
    {
        CONTEXT_ERROR(a_context,
                      "The folder being deleted is not in the path storage, "
                      "folder name: '%s'.",
                      a_folder_name);
    }

    return result;
}

bool
util::PathStorage::clearFolderNonstatic(std::string_view a_folder_name,
                                        const core::Context& a_context) noexcept
{
    bool result = false;
    if (removeFolderNonstatic(a_folder_name, a_context))
    {
        auto opt_path = touchFolderNonstatic(a_folder_name, &a_context);
        if (opt_path.has_value())
        {
            result = true;
        }
    }
    return result;
}

//------------------------------------------------------------------------------
// File system content handling
//------------------------------------------------------------------------------

void
util::PathStorage::addContentToPathsNonstatic(std::string_view a_path,
                                              ObjectType a_object_type,
                                              LevelType a_level_type) noexcept
{
    if (int(a_object_type) & int(ObjectType::FILE))
    {
        auto content =
            getContentNonstatic(a_path, ObjectType::FILE, a_level_type);
        for (auto& i : content)
        {
            addFileNonstatic(i);
        }
    }

    if (int(a_object_type) & int(ObjectType::FOLDER))
    {
        auto content =
            getContentNonstatic(a_path, ObjectType::FOLDER, a_level_type);
        for (auto& i : content)
        {
            addFolderNonstatic(Path::normalizeSeparators(i));
        }
    }
}

std::vector<std::string>
util::PathStorage::getContentNonstatic(std::string_view a_path,
                                       ObjectType a_object_type,
                                       LevelType a_level_type) noexcept
{
    std::vector<std::string> result;
    if (a_level_type == LevelType::CURRENT)
    {
        result = getContentImpl(std::filesystem::directory_iterator(a_path),
                                a_object_type);
    }
    else
    {
        result = getContentImpl(
            std::filesystem::recursive_directory_iterator(a_path),
            a_object_type);
    }
    return result;
}

// std::unordered_map<std::string, std::string>
// util::PathStorage::getContentMapNonstatic(std::string_view a_path,
//                                           ObjectType a_object_type,
//                                           LevelType a_level_type) noexcept
// {
//     std::unordered_map<std::string, std::string> result;

//     auto paths = getContent(aPath, aFIleType, aLevelType);
//     for (auto&& i : paths)
//     {
//         auto num = i.rfind("/", i.size() - 2);
//         auto key = i.substr(num + 1, i.size());
//         if (key.back() == '/') key.pop_back();
//         // TODO: check move existance
//         result.insert({std::move(key), std::move(i)});
//     }

//     return result;
// }
