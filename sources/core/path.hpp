#pragma once

//--------------------------------------------------------------------------------

#include <boost/optional.hpp>

#include <optional>
#include <unordered_map>

#include "domain/holy_trinity.hpp"

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Path
{
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

    static boost::optional<const str::string&> getFilePath(
        const str::string& aFileName) noexcept;
    static std::optional<str::string> getFilePath(
        const str::string& aFolderName, const str::string& aFileName) noexcept;

    static const str::string& getFilePathUnsafe(
        const str::string& aFileName) noexcept;
    static const str::string& getFilePathUnsafe(
        const str::string& aFolderName, const str::string& aFileName) noexcept;

    //----------------------------------------------------------------------------

    static boost::optional<const str::string&> getFolderPath(
        const str::string& aFolderName) noexcept;
    static const str::string& getFolderPathUnsafe(
        const str::string& aFolderName) noexcept;

    //----------------------------------------------------------------------------

    static std::optional<str::string> touchFolder(
        const str::string& aFolderParentPath,
        const str::string& aFolderName) noexcept;
    static bool clearFolder(const str::string& aFolderName) noexcept;

    //----------------------------------------------------------------------------

    static void addContentToPaths(const str::string& aPath,
                                  FileType aFIleType,
                                  LevelType aLevelType) noexcept;

    static std::vector<str::string> getContent(const str::string& aPath,
                                               FileType aFIleType,
                                               LevelType aLevelType) noexcept;

    static std::unordered_map<str::string, str::string> getContentMap(
        const str::string& aPath,
        FileType aFIleType,
        LevelType aLevelType) noexcept;

    //----------------------------------------------------------------------------

private:
    std::unordered_map<str::string, str::string> mFilesPaths;
    std::unordered_map<str::string, str::string> mFolderPaths;

    //----------------------------------------------------------------------------

    HOLY_TRINITY_SINGLE(Path);

    Path() noexcept;
    static Path& getInstance() noexcept;

    //----------------------------------------------------------------------------

    boost::optional<const str::string&> getPath(
        const std::unordered_map<str::string, str::string>& aStorage,
        const str::string& aName) noexcept;

    boost::optional<str::string> getPath(
        const str::string& aFolderName, const str::string& aFileName) noexcept;

    //----------------------------------------------------------------------------

    std::optional<str::string> touchFolderNonstatic(
        const str::string& aFolderParentPath,
        const str::string& aFolderName) noexcept;

    //----------------------------------------------------------------------------

    void addContentToMap(
        const str::string& aPath,
        FileType aType,
        LevelType aLevelType,
        std::unordered_map<str::string, str::string>& aPathMap) noexcept;

    template <typename PathIterator>
    static std::unordered_map<str::string, str::string> getContent(
        const PathIterator& aPath, FileType aFIleType) noexcept
    {
        std::vector<str::string> result;
        for (const auto& entry : aPath)
        {
            if (entry.is_directory() ? 2 : 1 & int(aFIleType))
            {
                str::string path = entry.path().string();

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

} // namespace core

//--------------------------------------------------------------------------------
