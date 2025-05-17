#include "path.hpp"

#include <filesystem>

#include "core/logging.hpp"

#include "string/kus_string.hpp"
#include "string/parser.hpp"

// #include "file.hpp"

//--------------------------------------------------------------------------------
//                                Path initialise
//--------------------------------------------------------------------------------

fs::Path::Path() noexcept
{
    // Set path to bin and its parant folders
    auto binPath        = std::filesystem::current_path();
    auto mainFolderPath = binPath.parent_path();

    auto binPathStr        = std::filesystem::current_path().string() + "/";
    auto mainFolderPathStr = binPath.parent_path().string() + "/";

    mFolderPaths.emplace("bin", binPathStr);
    auto configPathIt =
        mFolderPaths.emplace("config", mainFolderPathStr + "config/").first;
    mFolderPaths.emplace("main", std::move(mainFolderPathStr));
    mFolderPaths.emplace("data", std::move(binPathStr)); // default data folder
    // std::replace(binPath.begin(), binPath.end(), '\\', '/');

    // Add paths to all config files
    addContentToPathsNonstatic(configPathIt->second, FileType::File,
                               LevelType::Current);

    // Load paths from path config file
    // auto pathCfgFileIt = mFilesPaths.find("path.cfg");
    // if (pathCfgFileIt != mFilesPaths.end())
    // {
    //     auto paths =
    //     core::Parser::getVariablesFromFile(pathCfgFileIt->second); if
    //     (paths.empty())
    //     {
    //         LOG_WARNING("Path file doesn't exist or empty");
    //     }
    //     for (auto& var : paths)
    //     {
    //         if (var.value.getType() != core::Value::Type::String)
    //         {
    //             LOG_ERROR("'", var.name, "' from ", pathFile, " isn't path");
    //             continue;
    //         }

    //         mFolderPaths[var.name] = str::String(var.value);
    //         addAllFolders(var.value);
    //     }
    // }
}

fs::Path&
fs::Path::getInstance() noexcept
{
    static Path instance;
    return instance;
}

//--------------------------------------------------------------------------------
//                              Get file path static
//--------------------------------------------------------------------------------

boost::optional<const char*>
fs::Path::getFilePath(const char* aFileName) noexcept
{
    auto path = getInstance().getPath(getInstance().mFilesPaths, aFileName);
    if (!path.has_value())
    {
        LOG_WARNING("No such file(", aFileName, ")");
    }
    return path;
}

std::optional<str::String>
fs::Path::getFilePath(const char* aFolderName, const char* aFileName) noexcept
{
    auto path = getInstance().getPath(aFolderName, aFileName);
    if (!path.has_value())
    {
        LOG_WARNING("Can't reach file", aFileName, "- no such folder(",
                    aFolderName, ")");
    }
    return path;
}

//--------------------------------------------------------------------------------
//                         Get file path static unsafe
//--------------------------------------------------------------------------------

const char*
fs::Path::getFilePathUnsafe(const char* aFileName) noexcept
{
    auto path = getInstance().getPath(getInstance().mFilesPaths, aFileName);
    if (path.has_value())
    {
        return path.value();
    }
    else
    {
        LOG_ERROR("No such file(", aFileName, ")");
        return str::String::EMPTY_STRING;
    }
}

const char*
fs::Path::getFilePathUnsafe(const char* aFolderName,
                            const char* aFileName) noexcept
{
    auto path = getInstance().getPath(aFolderName, aFileName);
    if (path.has_value())
    {
        return path.value();
    }
    else
    {
        LOG_ERROR("Can't reach file", aFileName, "- no such folder(",
                  aFolderName, ")");
        return str::String::EMPTY_STRING;
    }
}

//--------------------------------------------------------------------------------
//                               Get folder path
//--------------------------------------------------------------------------------

boost::optional<const char*>
fs::Path::getFolderPath(const char* aFolderName) noexcept
{
    auto path = getInstance().getPath(getInstance().mFolderPaths, aFolderName);
    if (!path.has_value())
    {
        LOG_WARNING("No such folder(", aFolderName, ")");
    }
    return path;
}

const char*
fs::Path::getFolderPathUnsafe(const char* aFolderName) noexcept
{
    auto path = getInstance().getPath(getInstance().mFolderPaths, aFolderName);
    if (path.has_value())
    {
        return path.value();
    }
    else
    {
        LOG_ERROR("Can't reach file", aFolderName, "- no such folder(",
                  aFolderName, ")");
        return str::String::EMPTY_STRING;
    }
}

//--------------------------------------------------------------------------------
//                               Basic get path
//--------------------------------------------------------------------------------

boost::optional<const char*>
fs::Path::getPath(const std::unordered_map<str::String, str::String>& aStorage,
                  const char* aName) noexcept
{
    boost::optional<const char*> result;
    auto it = aStorage.find(aName);
    if (it != aStorage.end())
    {
        result = it->second;
    }
    return result;
}

std::optional<str::String>
fs::Path::getPath(const char* aFolderName, const char* aFileName) noexcept
{

    std::optional<str::String> result;
    auto it = mFolderPaths.find(aFolderName);
    if (it != mFolderPaths.end())
    {
        result = str::String(it->second, aFileName);
    }
    return result;
}

//--------------------------------------------------------------------------------
//                               Folder manipulations
//--------------------------------------------------------------------------------

// std::optional<str::String>
// fs::Path::touchFolder(const char* aFolderParentPath,
//                       const char* aFolderName) noexcept
// {
//     return getInstance().touchFolderNonstatic(aFolderParentPath, aFolderName);
// }

// std::optional<str::String>
// fs::Path::touchFolderNonstatic(const char* aFolderParentPath,
//                                const char* aFolderName) noexcept
// {
//     std::optional<str::String> result;

//     str::String fullPath = aFolderParentPath + "/" + aFolderName + "/";
//     auto storedPath      = getPath(mFolderPaths, aFolderName);
//     // TODO: check for existance on disk
//     if (!storedPath.has_value())
//     {
//         if (std::filesystem::create_directories(fullPath.getStdStringRef()))
//         {
//             LOG_INFO("Create folder (Path:", aFolderParentPath,
//                      " Name:", aFolderName);
//             result = mFolderPaths.emplace(aFolderName, std::move(fullPath))
//                          .first->second;
//         }
//         else
//         {
//             LOG_ERROR("Can't create folder (Path:", aFolderParentPath,
//                       " Name:", aFolderName);
//         }
//     }
//     else
//     {
//         if (storedPath.value() == fullPath)
//         {
//             LOG_INFO("Touch  existed folder (Path:", aFolderParentPath,
//                      " Name:", aFolderName);
//             result = std::move(storedPath.value());
//         }
//         else
//         {
//             LOG_ERROR("Touched folder already exist in memory (Path:",
//                       aFolderParentPath, " Name:", aFolderName);
//         }
//     }

//     return result;
// }

bool
fs::Path::clearFolder(const char* aFolderName) noexcept
{
    bool result = false;

    str::String temp;
    auto folderPath =
        getInstance().getPath(getInstance().mFolderPaths, aFolderName);
    if (folderPath.has_value())
    {
        result = std::filesystem::remove_all(temp.getStdStringRef());
        result &= std::filesystem::create_directories(temp.getStdStringRef());
        if (result)
        {
            LOG_INFO("Clear folder (", aFolderName, ")");
        }
        else
        {
            LOG_ERROR("Unexpected error while clearing folder (", aFolderName,
                      ")");
        }
    }
    else
    {
        LOG_ERROR("Folder scheduled for cleaning doesn't exist (", aFolderName,
                  ")");
    }

    return result;
}

//--------------------------------------------------------------------------------
//                                 Content handler
//--------------------------------------------------------------------------------

void
fs::Path::addContentToMap(
    const char* aPath,
    FileType aType,
    LevelType aLevelType,
    std::unordered_map<str::String, str::String>& aPathMap) noexcept
{
    auto temp = getContentMap(aPath, aType, aLevelType);
    aPathMap.insert(temp.begin(), temp.end());
}

void
fs::Path::addContentToPaths(const char* aPath,
                            FileType aFIleType,
                            LevelType aLevelType) noexcept
{
    getInstance().addContentToPathsNonstatic(aPath, aFIleType, aLevelType);
}

void
fs::Path::addContentToPathsNonstatic(const char* aPath,
                                     FileType aFIleType,
                                     LevelType aLevelType) noexcept
{
    if (int(aFIleType) & int(FileType::File))
    {
        addContentToMap(aPath, FileType::File, aLevelType, mFilesPaths);
    }
    if (int(aFIleType) & int(FileType::Folder))
    {
        addContentToMap(aPath, FileType::Folder, aLevelType, mFolderPaths);
    }
}

std::vector<PathData>
fs::Path::getContent(const char* aPath,
                     FileType aFIleType,
                     LevelType aLevelType) noexcept
{
    std::vector<str::String> result;
    if (aLevelType == LevelType::Current)
    {
        result = getContent(
            std::filesystem::directory_iterator(aPath.getStdStringRef()),
            aFIleType);
    }
    else
    {
        result = getContent(std::filesystem::recursive_directory_iterator(
                                aPath.getStdStringRef()),
                            aFIleType);
    }
    return result;
}

std::unordered_map<str::String, str::String>
fs::Path::getContentMap(const char* aPath,
                        FileType aFIleType,
                        LevelType aLevelType) noexcept
{
    std::unordered_map<str::String, str::String> result;

    auto paths = getContent(aPath, aFIleType, aLevelType);
    for (auto&& i : paths)
    {
        auto num = i.rfind("/", i.size() - 2);
        auto key = i.substr(num + 1, i.size());
        if (key.back() == '/') key.pop_back();
        // TODO: check move existance
        result.insert({std::move(key), std::move(i)});
    }

    return result;
}
