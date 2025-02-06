#include "path_storage.hpp"

#include <filesystem>

#include "kernel/framework/logging/logging.hpp"

#include "path_values.hpp"

//------------------------------------------------------------------------------
// Path storage initialization
//------------------------------------------------------------------------------

util::PathStorage::PathStorage()
{
    auto cur_path_val = std::filesystem::current_path();
    auto bin_path     = cur_path_val.string();
    auto app_path     = cur_path_val.parent_path().string();

    m_folder_paths.emplace(BIN_PATH_NAME, bin_path);
    m_folder_paths.emplace(APP_PATH_NAME, app_path);
    m_folder_paths.emplace(DATA_FOLDER_NAME, app_path);
    addFolder(APP_PATH_NAME, DATA_FOLDER_NAME);

    // addContentToPathsNonstatic(app_folder_path_str, ObjectType::FOLDER,
    //                            LevelType::CURRENT);
}

//------------------------------------------------------------------------------
// Getting paths from the storage
//------------------------------------------------------------------------------

const std::string&
util::PathStorage::getFilePath(const std::string& a_file_name) const
{
    return m_files_paths.find(a_file_name)->second;
}

const std::string&
util::PathStorage::getFolderPath(const std::string& a_folder_name) const
{
    return m_folder_paths.find(a_folder_name)->second;
}

//------------------------------------------------------------------------------
// Adding paths to the storage
//------------------------------------------------------------------------------

const std::string&
util::PathStorage::addFile(const std::string& a_parent_name,
                           const std::string& a_file_name)
{
    // TODO: make it better
    auto& parent_path                  = getFolderPath(a_parent_name);
    return m_folder_paths[a_file_name] = parent_path + "/" + a_file_name;
}

const std::string&
util::PathStorage::addFolder(const std::string& a_parent_name,
                             const std::string& a_folder_name)
{
    // TODO: make it better
    auto& parent_path = getFolderPath(a_parent_name);
    auto& res_path    = m_folder_paths[a_folder_name] =
        parent_path + "/" + a_folder_name;
    touchFolder(res_path);
    return res_path;
}

//--------------------------------------------------------------------------------
// Folder manipulation
//--------------------------------------------------------------------------------

// TODO: exeption safety?
void
util::PathStorage::touchFolder(const std::string& a_folder_path)
{
    // LOG_INFO("Create folder with path '%s'.", a_folder_path);
    std::filesystem::create_directories(a_folder_path);
    // LOG_CATCH(std::filesystem::create_directories(a_folder_path),
    // (*a_context),
    //           "Unable to create folder with path: '%s'.", a_folder_path);
}

// bool
// util::PathStorage::removeFolderNonstatic(
//     std::string_view a_folder_name,
//     const core::Context& a_context) noexcept
// {
//     bool result = false;

//     auto folderPath = getFolderPathNonstatic(a_folder_name);
//     if (folderPath.has_value())
//     {
//         auto& folder_path = folderPath.value();
//         m_folder_paths.erase(a_folder_name);
//         LOG_CATCH(result = std::filesystem::remove_all(folder_path),
//         a_context,
//                   "Failed to delete folder, name: '%s', path: '%s'.",
//                   a_folder_name, folder_path);
//         if (result)
//         {
//             CONTEXT_INFO(a_context, "Delete folder named '%s'.",
//             folder_path);
//         }
//         else
//         {
//             CONTEXT_ERROR(a_context,
//                           "Unexpected error when deleting a folder '%s'.",
//                           folder_path);
//         }
//     }
//     else
//     {
//         CONTEXT_ERROR(a_context,
//                       "The folder being deleted is not in the path storage, "
//                       "folder name: '%s'.",
//                       a_folder_name);
//     }

//     return result;
// }

// bool
// util::PathStorage::clearFolderNonstatic(std::string_view a_folder_name,
//                                         const core::Context& a_context)
// {
//     bool result = false;

//     auto folderPath = getFolderPathNonstatic(a_folder_name);
//     if (folderPath.has_value())
//     {
//         auto& folder_path = folderPath.value();
//         m_folder_paths.erase(a_folder_name);
//         LOG_CATCH(result = std::filesystem::remove_all(folder_path),
//         a_context,
//                   "Failed to delete folder, name: '%s', path: '%s'.",
//                   a_folder_name, folder_path);
//         if (result)
//         {
//             auto opt_path = touchFolderNonstatic(a_folder_name, &a_context);
//                     if (opt_path.has_value())
//         {
//             result = true;
//         }
//             CONTEXT_INFO(a_context, "Delete folder named '%s'.",
//             folder_path);
//         }
//         else
//         {
//             CONTEXT_ERROR(a_context,
//                           "Unexpected error when deleting a folder '%s'.",
//                           folder_path);
//         }
//     }
//     else
//     {
//         CONTEXT_ERROR(a_context,
//                       "The folder being deleted is not in the path storage, "
//                       "folder name: '%s'.",
//                       a_folder_name);
//     }

//     return result;
// }

//------------------------------------------------------------------------------
// File system content handling
//------------------------------------------------------------------------------

// void
// util::PathStorage::addContentToPathsNonstatic(std::string_view a_path,
//                                               ObjectType a_object_type,
//                                               LevelType a_level_type)
//                                               noexcept
// {
//     if (int(a_object_type) & int(ObjectType::FILE))
//     {
//         auto content =
//             getContentNonstatic(a_path, ObjectType::FILE, a_level_type);
//         for (auto& i : content)
//         {
//             addFileNonstatic(i);
//         }
//     }

//     if (int(a_object_type) & int(ObjectType::FOLDER))
//     {
//         auto content =
//             getContentNonstatic(a_path, ObjectType::FOLDER, a_level_type);
//         for (auto& i : content)
//         {
//             addFolderNonstatic(i);
//         }
//     }
// }

// std::vector<std::string>
// util::PathStorage::getContentNonstatic(std::string_view a_path,
//                                        ObjectType a_object_type,
//                                        LevelType a_level_type) noexcept
// {
//     std::vector<std::string> result;
//     if (a_level_type == LevelType::CURRENT)
//     {
//         result = getContentImpl(std::filesystem::directory_iterator(a_path),
//                                 a_object_type);
//     }
//     else
//     {
//         result = getContentImpl(
//             std::filesystem::recursive_directory_iterator(a_path),
//             a_object_type);
//     }
//     return result;
// }

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
