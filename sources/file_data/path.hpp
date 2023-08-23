#ifndef KUS_PATHS_HPP
#define KUS_PATHS_HPP

#include <boost/optional.hpp>

#include <algorithm>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "domain/holy_trinity.hpp"

namespace file
{
class Path
{
public:
    HOLY_TRINITY_SINGLE(Path);

    static boost::optional<const std::string&> getPath(
        const std::string& aName, bool aIsCritical = false) noexcept;
    static std::optional<std::string> getPath(
        const std::string& aFolder,
        const std::string& aName,
        bool aIsCritical = false) noexcept;

    static std::string getPathUnsafe(const std::string& aFolder) noexcept;
    static std::string getPathUnsafe(const std::string& aFolder,
                                     const std::string& aName) noexcept;

    static std::optional<std::string> openFolder(
        const std::string& aName) noexcept;
    static bool clearFolder(const std::string& aName) noexcept;

    static void addFoldersFrom(const std::string& aPath) noexcept;

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
    static std::vector<std::string> getContent(
        const std::string& aPath,
        FileType aFIleType   = FileType::File,
        LevelType aLevelType = LevelType::Current) noexcept;
    static std::unordered_map<std::string, std::string> getContentMap(
        const std::string& aPath,
        FileType aFIleType,
        LevelType aLevelType) noexcept;

private:
    std::unordered_map<std::string, std::string> mPaths;
    static std::unordered_set<std::string> mForbiddenFolders;

    Path() noexcept;
    static Path& getInstance() noexcept;
    void reset() noexcept;

    void addAllFolders(const std::string& aPath) noexcept;

    template <typename TLevel>
    static std::vector<std::string> getContent(const std::string& aPath,
                                               FileType aFIleType) noexcept
    {
        std::vector<std::string> result;
        for (const auto& entry : TLevel(aPath))
        {
            if (entry.is_directory() ? 2 : 1 & int(aFIleType))
            {
                std::string path = entry.path().string();
                std::replace(path.begin(), path.end(), '\\', '/');

                bool flag = false;
                for (auto& i : mForbiddenFolders)
                {
                    if (path.find(i) != std::string::npos)
                    {
                        flag = true;
                        break;
                    }
                }
                if (flag) continue;

                result.emplace_back(path + (entry.is_directory() ? "/" : ""));
            }
        }
        return result;
    }
};
} // namespace file

#endif // !KUS_PATHS_HPP
