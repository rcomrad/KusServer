#pragma once

//------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "core/logging/context.hpp"

#include "utility/common/holy_trinity.hpp"

#include "path.hpp"

//------------------------------------------------------------------------------

namespace util
{

class PathStorage
{
public:
    HOLY_TRINITY_SINGLETON(PathStorage);

    //--------------------------------------------------------------------------

public:
    SINGL_RET_METHOD(std::optional<std::string_view>,
                     addFile,
                     (std::string_view a_folder_name,
                      std::string_view a_file_name,
                      const core::Context* a_context = nullptr));

    SINGL_RET_METHOD(std::optional<std::string_view>,
                     addFolder,
                     (std::string_view a_folder_name,
                      std::string_view a_folder_path,
                      const core::Context* a_context = nullptr));

private:
    std::optional<std::string_view> addFileNonstatic(
        std::string_view a_folder_path,
        const core::Context* a_context = nullptr) noexcept;

    std::optional<std::string_view> addFolderNonstatic(
        std::string_view a_folder_path,
        const core::Context* a_context = nullptr) noexcept;

    std::optional<std::string_view> addObject(
        std::unordered_map<std::string_view, std::string>& a_storage,
        std::string_view a_name,
        std::string_view a_path,
        const core::Context* a_context,
        bool a_is_folder) noexcept;

    //--------------------------------------------------------------------------

public:
    // TODO: rewrite singleton metchod generator

    // SINGL_RET_METHOD(std::optional<auto>,
    //                  getFilePath,
    //                  (std::string_view a_file_name,
    //                   const core::Context* a_context = nullptr));

    template <typename... Args>
    static auto getFilePath(Args... args)
    {
        return getInstance().getFilePathNonstatic(std::forward<Args>(args)...);
    }

    SINGL_RET_METHOD(std::optional<std::string_view>,
                     getFolderPath,
                     (std::string_view a_folder_name,
                      const core::Context* a_context = nullptr));

private:
    std::optional<std::string_view> getFilePathNonstatic(
        std::string_view a_file_name,
        const core::Context* a_context = nullptr) noexcept;

    std::optional<std::string> getFilePathNonstatic(
        std::string_view a_folder_name,
        std::string_view a_file_name,
        const core::Context* a_context = nullptr) noexcept;

    std::optional<std::string_view> searchInStorage(
        std::unordered_map<std::string_view, std::string>& a_storage,
        const std::string_view& a_key,
        const core::Context* a_context,
        const char* a_msg) noexcept;

    //--------------------------------------------------------------------------

public:
    SINGL_RET_METHOD(std::optional<std::string_view>,
                     touchFolder,
                     (std::string_view a_folder_name,
                      std::string_view a_parent_path,
                      const core::Context* a_context = nullptr));

    SINGL_RET_METHOD(bool,
                     removeFolder,
                     (std::string_view a_folder_name,
                      const core::Context& a_context));

    SINGL_RET_METHOD(bool,
                     clearFolder,
                     (std::string_view a_folder_name,
                      const core::Context& a_context));

private:
    std::optional<std::string_view> touchFolderNonstatic(
        std::string_view a_full_path,
        const core::Context* a_context = nullptr) noexcept;

    std::optional<std::string_view> touchFolderImpl(
        std::string_view a_folder_name,
        std::string_view a_full_path,
        const core::Context* a_context) noexcept;

    //----------------------------------------------------------------------------

public:
    enum class ObjectType
    {
        NUN    = 0,
        FILE   = 1,
        FOLDER = 2,
        ALL    = 3
    };
    enum class LevelType
    {
        CURRENT,
        RECURSIVE
    };

    SINGL_VOID_METHOD(addContentToPaths,
                      (std::string_view a_path,
                       ObjectType a_object_type,
                       LevelType a_level_type));

    SINGL_RET_METHOD(std::vector<std::string>,
                     getContent,
                     (std::string_view a_path,
                      ObjectType a_object_type,
                      LevelType a_level_type));

    // SINGL_RET_METHOD(std::unordered_map<std::string, std::string>,
    //                  getContentMap,
    //                  (std::string_view a_path,
    //                   ObjectType a_object_type,
    //                   LevelType a_level_type));

    //----------------------------------------------------------------------------

private:
    // TODO: unordered_map with ptr count?
    std::unordered_set<std::string> m_str_storage;
    std::unordered_map<std::string_view, std::string> m_files_paths;
    std::unordered_map<std::string_view, std::string> m_folder_paths;

    PathStorage() noexcept;

    template <typename DirIterator>
    static std::vector<std::string> getContentImpl(
        const DirIterator& a_dir_it,
        ObjectType a_object_type) noexcept
    {
        std::vector<std::string> result;
        for (const auto& entry : a_dir_it)
        {
            bool is_dir = entry.is_directory();
            if ((is_dir ? int(ObjectType::FOLDER) : int(ObjectType::FILE)) &
                int(a_object_type))
            {
                std::string path = entry.path().string();
                if (is_dir)
                {
                    path = Path::normalizeFolderPath(path, true);
                }

                result.emplace_back(std::move(path));
            }
        }
        return result;
    }
};
} // namespace util

#define GET_FILE_PATH(name, ...)                                   \
    auto name##_opt = util::PathStorage::getFilePath(__VA_ARGS__); \
    if (!name##_opt.has_value()) return;                           \
    auto& name = name##_opt.value();

//------------------------------------------------------------------------------
