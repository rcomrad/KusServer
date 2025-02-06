#pragma once

//------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

//------------------------------------------------------------------------------

namespace util
{

class PathStorage
{
public:
    PathStorage();

    // TODO: exeption safety?
    const std::string& getFilePath(const std::string& a_file_name) const;
    const std::string& getFolderPath(const std::string& a_folder_name) const;

    const std::string& addFile(const std::string& a_parent_name,
                               const std::string& a_file_name);
    const std::string& addFolder(const std::string& a_parent_name,
                                 const std::string& a_folder_name);

private:
    std::unordered_map<std::string, std::string> m_files_paths;
    std::unordered_map<std::string, std::string> m_folder_paths;

    void touchFolder(const std::string& a_folder_path);

public:
    // SINGL_RET_METHOD(bool,
    //                  removeFolder,
    //                  (std::string_view a_folder_name,
    //                   const core::Context& a_context));

    // bool clearFolder(std::string_view a_folder_name,
    //                  const core::Context& a_context);

    // private:
    //     std::optional<std::string_view> touchFolderNonstatic(
    //         std::string_view a_full_path,
    //         const core::Context* a_context = nullptr) noexcept;

    //     std::optional<std::string_view> touchFolderImpl(
    //         std::string_view a_folder_name,
    //         std::string_view a_full_path,
    //         const core::Context* a_context) noexcept;

    //     //----------------------------------------------------------------------------

    // public:
    //     enum class ObjectType
    //     {
    //         NUN    = 0,
    //         FILE   = 1,
    //         FOLDER = 2,
    //         ALL    = 3
    //     };
    //     enum class LevelType
    //     {
    //         CURRENT,
    //         RECURSIVE
    //     };

    //     SINGL_VOID_METHOD(addContentToPaths,
    //                       (std::string_view a_path,
    //                        ObjectType a_object_type,
    //                        LevelType a_level_type));

    //     SINGL_RET_METHOD(std::vector<std::string>,
    //                      getContent,
    //                      (std::string_view a_path,
    //                       ObjectType a_object_type,
    //                       LevelType a_level_type));

    // SINGL_RET_METHOD(std::unordered_map<std::string, std::string>,
    //                  getContentMap,
    //                  (std::string_view a_path,
    //                   ObjectType a_object_type,
    //                   LevelType a_level_type));

    //----------------------------------------------------------------------------

    // private:
    //     // TODO: unordered_map with ptr count?
    //     std::unordered_set<std::string> m_str_storage;
    //     std::unordered_map<std::string_view, std::string> m_files_paths;
    //     std::unordered_map<std::string_view, std::string> m_folder_paths;

    //     PathStorage() noexcept;

    //     template <typename DirIterator>
    //     static std::vector<std::string> getContentImpl(
    //         const DirIterator& a_dir_it,
    //         ObjectType a_object_type) noexcept
    //     {
    //         std::vector<std::string> result;
    //         for (const auto& entry : a_dir_it)
    //         {
    //             bool is_dir = entry.is_directory();
    //             if ((is_dir ? int(ObjectType::FOLDER) :
    //             int(ObjectType::FILE)) &
    //                 int(a_object_type))
    //             {
    //                 std::string path = entry.path().string();
    //                 if (is_dir)
    //                 {
    //                     path = Path::normalizeFolderPath(path, true);
    //                 }

    //                 result.emplace_back(std::move(path));
    //             }
    //         }
    //         return result;
    //     }
};
} // namespace util

//------------------------------------------------------------------------------
