#include "path.hpp"

#include <filesystem>

#include "domain/log.hpp"

#include "string/kus_string.hpp"

#include "file.hpp"
#include "parser.hpp"

//--------------------------------------------------------------------------------
//                                Path initialise
//--------------------------------------------------------------------------------

core::Path::Path() noexcept
{
    // Set path to bin and its parant folders
    auto binPath        = std::filesystem::current_path();
    auto mainFolderPath = binPath.parent_path();

    auto binPathStr        = std::filesystem::current_path().string() + "/";
    auto mainFolderPathStr = binPath.parent_path().string() + "/";

    mFolderPaths.insert({"bin", binPathStr});
    auto configPathIt =
        mFolderPaths.insert({"config", mainFolderPathStr + "config/"}).first;
    mFolderPaths.insert({"main", std::move(mainFolderPathStr)});
    mFolderPaths.insert({"data", std::move(binPathStr)}); // default data folder
    // std::replace(binPath.begin(), binPath.end(), '\\', '/');

    // Add paths to all config files
    addContentToPaths(configPathIt->second, FileType::File, LevelType::Current);

    // Load paths from path config file
    auto pathCfgFileIt = mFilesPaths.find("path.cfg");
    if (pathCfgFileIt != mFilesPaths.end())
    {
        auto paths = core::Parser::getVariablesFromFile(pathCfgFileIt->second);
        if (paths.empty())
        {
            LOG_WARNING("Path file doesn't exist or empty");
        }
        for (auto& var : paths)
        {
            if (var.value.getType() != core::Value::Type::String)
            {
                dom::writeError("'", var.name, "' from ", pathFile,
                                " isn't path");
                continue;
            }

            mFolderPaths[var.name] = str::string(var.value);
            addAllFolders(var.value);
        }
    }
}

core::Path&
core::Path::getInstance() noexcept
{
    static Path instance;
    return instance;
}

//--------------------------------------------------------------------------------
//                              Get file path static
//--------------------------------------------------------------------------------

boost::optional<const str::string&>
core::Path::getFilePath(const str::string& aFileName) noexcept
{
    auto path = getInstance().getPath(getInstance().mFilesPaths, aFileName);
    // if (!path.has_value())
    // {
    //     LOG_WARNING("No such file(", aFileName, ")");
    // }
    return path;
}

std::optional<str::string>
core::Path::getFilePath(const str::string& aFolderName,
                        const str::string& aFileName) noexcept
{
    auto path = getInstance().getPath(aFolderName, aFileName);
    // if (!path.has_value())
    // {
    //     LOG_WARNING("Can't reach file", aFileName, "- no such folder(",
    //                 aFolderName, ")");
    // }
    return path;
}

//--------------------------------------------------------------------------------
//                         Get file path static unsafe
//--------------------------------------------------------------------------------

const str::string&
core::Path::getFilePathUnsafe(const str::string& aFileName) noexcept
{
    auto path = getInstance().getPath(getInstance().mFilesPaths, aFileName);
    if (path.has_value())
    {
        return path.value();
    }
    else
    {
        LOG_ERROR("No such file(", aFileName, ")");
        return str::EMPTY_STRING;
    }
}

str::string
core::Path::getFilePathUnsafe(const str::string& aFolderName,
                              const str::string& aFileName) noexcept
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
        return str::EMPTY_STRING;
    }
}

//--------------------------------------------------------------------------------
//                               Get folder path
//--------------------------------------------------------------------------------

boost::optional<const str::string&>
core::Path::getFolderPath(const str::string& aFolderName) noexcept
{
    auto path = getInstance().getPath(getInstance().mFolderPaths, aFolderName);
    if (!path.has_value())
    {
        LOG_WARNING("No such folder(", aFolderName, ")");
    }
    return path;
}

const str::string&
core::Path::getFolderPathUnsafe(const str::string& aFolderName) noexcept
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
        return str::EMPTY_STRING;
    }
}

//--------------------------------------------------------------------------------
//                               Basic get path
//--------------------------------------------------------------------------------

boost::optional<const str::string&>
core::Path::getPath(
    const std::unordered_map<str::string, str::string>& aStorage,
    const str::string& aName) noexcept
{
    boost::optional<const str::string&> result;
    auto it = aStorage.find(aName);
    if (it != aStorage.end())
    {
        result = it->second;
    }
    return result;
}

boost::optional<const str::string&>
core::Path::getPath(const str::string& aFolderName,
                    const str::string& aFileName) noexcept
{

    boost::optional<const str::string&> result;
    auto it = aStorage.find(aName);
    if (it != aStorage.end())
    {
        result = it->second;
    }
    return result;
}

//--------------------------------------------------------------------------------
//                               Folder manipulations
//--------------------------------------------------------------------------------

std::optional<str::string>
core::Path::touchFolder(const str::string& aFolderParentPath,
                        const str::string& aFolderName) noexcept
{
    return getInstance().touchFolderNonstatic();
}

std::optional<str::string>
core::Path::touchFolderNonstatic(const str::string& aFolderParentPath,
                                 const str::string& aFolderName) noexcept
{
    std::optional<str::string> result;

    str::string fullPath = aFolderParentPath + "/" + aFolderName + "/";
    auto storedPath      = getPath(mFolderPaths, aFolderName);
    // TODO: check for existance on disk
    if (!storedPath.has_value())
    {
        if (std::filesystem::create_directories(fullPath))
        {
            LOG_INFO("Create folder (Path:", aFolderParentPath,
                     " Name:", aFolderName);
            result = mFolderPaths.insert({aFolderName, std::move(fullPath)})
                         .fisert.second;
        }
        else
        {
            LOG_ERROR("Can't create folder (Path:", aFolderParentPath,
                      " Name:", aFolderName);
        }
    }
    else
    {
        if (storedPath.value() == fullPath)
        {
            LOG_INFO("Touch  existed folder (Path:", aFolderParentPath,
                     " Name:", aFolderName);
            result = storedPath.value();
        }
        else
        {
            LOG_ERROR("Touched folder already exist in memory (Path:",
                      aFolderParentPath, " Name:", aFolderName);
        }
    }

    return result;
}

bool
core::Path::clearFolder(const str::string& aFolderName) noexcept
{
    bool result = false;

    str::string temp;
    auto folderPath =
        getInstance().getPath(getInstance().mFolderPaths, aFolderName);
    if (folderPath.has_value())
    {
        result = std::filesystem::remove_all(temp);
        result &= std::filesystem::create_directories(temp);
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
core::Path::addContentToMap(
    const str::string& aPath,
    FileType aType,
    LevelType aLevelType,
    std::unordered_map<str::string, str::string>& aPathMap) noexcept
{
    auto temp = getContentMap(aPath, aType, aLevelType);
    aPathMap.insert(temp.begin(), temp.end());
}

void
core::Path::addContentToPaths(const str::string& aPath,
                              FileType aFIleType,
                              LevelType aLevelType) noexcept
{
    if (aFIleType & FileType::File)
    {
        addContentToMap(aPath, FileType::File, aLevelType, mFilesPaths);
    }
    if (aFIleType & FileType::Folder)
    {
        addContentToMap(aPath, FileType::Folder, aLevelType, mFolderPaths);
    }
}

std::vector<str::string>
core::Path::getContent(const str::string& aPath,
                       FileType aFIleType,
                       LevelType aLevelType) noexcept
{
    std::vector<str::string> result;
    if (aLevelType == LevelType::Current)
    {
        result =
            getContent(std::filesystem::directory_iterator(aPath), aFIleType);
    }
    else
    {
        result = getContent(
            std::filesystem::recursive_directory_iterator(aPath), aFIleType);
    }
    return result;
}

std::map<str::string, str::string>
core::Path::getContentMap(const str::string& aPath,
                          FileType aFIleType,
                          LevelType aLevelType) noexcept
{
    std::map<str::string, str::string> result;

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
