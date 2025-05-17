#pragma once

//--------------------------------------------------------------------------------

#include "core/holy_trinity.hpp"

#include "kus_standard/char_buffer.hpp"
#include "kus_standard/hash_map_by_str.hpp"
#include "kus_standard/kus_optional.hpp"

//--------------------------------------------------------------------------------

namespace fs
{
class Path
{
private:
    enum
    {
        MAX_PATH_LENGTH      = 200,
        MAX_FILE_NAME_LENGTH = 50
    };

    inline static const char PathName[] = "Path";

    using PathData = kstd::CharVector;
    using PathMap =
        kstd::HashMapByStr<PathName, MAX_FILE_NAME_LENGTH, PathData>;

public:
    enum class FileType
    {
        Nun    = 0,
        File   = 1,
        Folder = 2,
        All    = 3
    };
    enum class LevelType
    {
        Nun,
        Current,
        Recursive
    };

    //----------------------------------------------------------------------------

    static kstd::OptionalPtr<const char> getFilePath(
        const char* aFileName) noexcept;
    static kstd::OptionalValue<PathData> getFilePath(
        const char* aFolderName,
        const char* aFileName) noexcept;

    //----------------------------------------------------------------------------

    static kstd::OptionalPtr<const char> getFolderPath(
        const char* aFolderName) noexcept;

    //----------------------------------------------------------------------------

    // static kstd::OptionalPtr<const char> touchFolder(
    //     const char* aFolderParentPath,
    //     const char* aFolderName) noexcept;
    static bool clearFolder(const char* aFolderName) noexcept;

    //----------------------------------------------------------------------------

    static void addContentToPaths(const char* aPath,
                                  FileType aFIleType,
                                  LevelType aLevelType) noexcept;

    static std::vector<PathData> getContent(const char* aPath,
                                            FileType aFIleType,
                                            LevelType aLevelType) noexcept;

    static PathMap getContentMap(const char* aPath,
                                 FileType aFIleType,
                                 LevelType aLevelType) noexcept;

    //----------------------------------------------------------------------------

private:
    PathMap mFilesPaths;
    PathMap mFolderPaths;

    //----------------------------------------------------------------------------

    HOLY_TRINITY_SINGLE(Path);

    Path() noexcept;
    static Path& getInstance() noexcept;

    //----------------------------------------------------------------------------

    kstd::OptionalPtr<const char> getPath(const PathMap& aStorage,
                                          const char* aName) noexcept;

    kstd::OptionalPtr<const char> getPath(const char* aFolderName,
                                          const char* aFileName) noexcept;

    //----------------------------------------------------------------------------

    kstd::OptionalPtr<const char> touchFolderNonstatic(
        const char* aFolderParentPath,
        const char* aFolderName) noexcept;

    //----------------------------------------------------------------------------

    void addContentToPathsNonstatic(const char* aPath,
                                    FileType aFIleType,
                                    LevelType aLevelType) noexcept;

    void addContentToMap(const char* aPath,
                         FileType aType,
                         LevelType aLevelType,
                         PathMap& aPathMap) noexcept;

    template <typename PathIterator>
    static std::vector<PathData> getContent(const PathIterator& aPath,
                                            FileType aFIleType) noexcept
    {
        std::vector<str::String> result;
        for (const auto& entry : aPath)
        {
            if (entry.is_directory() ? 2 : 1 & int(aFIleType))
            {
                str::String path = entry.path().string();

                // #ifdef BILL_WINDOWS
                //                 std::replace(path.begin(), path.end(), '\\',
                //                 '/');
                // #endif

                if (entry.is_directory()) path.push_back('/');

                result.emplace_back(std::move(path));
            }
        }
        return result;
    }
};

} // namespace fs

//--------------------------------------------------------------------------------
