#include "path.hpp"

#include <filesystem>

#include "general_tools/log.hpp"

#include "file.hpp"
#include "parser.hpp"
// #include "variable_storage.hpp"

//--------------------------------------------------------------------------------

#if defined(BILL_WINDOWS)
#    include <windows.h>
#elif defined(LINUS_LINUX)
#    include <limits.h>
#    include <unistd.h>
#endif

//--------------------------------------------------------------------------------

text::Path::Path() noexcept
{
    reset();
    mForbiddenFolders = {"/.", "/build", "/cmake_scripts", "/devops"};
}

text::Path&
text::Path::getInstance() noexcept
{
    static Path instance;
    return instance;
}

void
text::Path::reset() noexcept
{
    mPaths["main"] =
        std::filesystem::current_path().parent_path().string() + "/";
    std::replace(mPaths["main"].begin(), mPaths["main"].end(), '\\', '/');
    addAllFolders(mPaths["main"]);
    mPaths["data"] = mPaths["main"];

    auto pathFile = mPaths["config"] + "path.conf";
    auto paths    = text::Parser::getVariablesFromFile(pathFile);
    if (paths.empty())
    {
        LOG_WARNING("Path file doesn't exist or empty");
    }
    for (auto& var : paths)
    {
        if (var.value.getType() != text::Value::Type::String)
        {
            LOG_ERROR("'", var.name, "' from ", pathFile, " isn't path");
            continue;
        }

        mPaths[var.name] = std::string(var.value);
        addAllFolders(var.value);
    }
}

//--------------------------------------------------------------------------------

boost::optional<const std::string&>
text::Path::getPath(const std::string& aName, bool aIsCritical) noexcept
{
    boost::optional<const std::string&> result;

    auto& storage = getInstance().mPaths;

    auto it = storage.find(aName);
    if (it != storage.end()) result = it->second;
    else
    {
        if (aIsCritical)
        {
            LOG_ERROR("No such path (", aName, ")");
        }
        else
        {
            LOG_WARNING("No such path (", aName, ")");
        }
    }

    return result;
}

std::optional<std::string>
text::Path::getPath(const std::string& aFolder,
                    const std::string& aName,
                    bool aIsCritical) noexcept
{
    std::optional<std::string> result;

    auto folder = getPath(aFolder);
    if (folder.has_value())
    {
        result = folder.value() + aName;
    }
    else
    {
        if (aIsCritical)
        {
            LOG_ERROR("No such folder (", aFolder, ")");
        }
        else
        {
            LOG_WARNING("No such folder (", aFolder, ")");
        }
    }

    return result;
}

std::string
text::Path::getPathUnsafe(const std::string& aFolder) noexcept
{
    return getPathUnsafeTempl(aFolder);
}

std::string
text::Path::getPathUnsafe(const std::string& aFolder,
                          const std::string& aName) noexcept
{
    return getPathUnsafeTempl(aFolder, aName);
}

std::optional<std::string>
text::Path::touchFolder(const std::string& aName) noexcept
{
    std::optional<std::string> result;

    auto& ins = getInstance();

    auto temp = ins.getPath(aName);
    if (!temp.has_value())
    {
        LOG_WARNING("No such path (", aName, ")");

        std::string path = ins.mPaths["data"] + aName + "/";
        if (std::filesystem::create_directories(path))
        {
            result = ins.mPaths[aName] = path;
            LOG_INFO("Creating path", aName, " (", path, ")");
        }
        else
        {
            LOG_ERROR("Can't creating path", aName, " (", path, ")");
        }
    }
    else
    {
        result = temp.value();
    }

    return result;
}

bool
text::Path::clearFolder(const std::string& aName) noexcept
{
    bool result = false;

    std::string temp;
    auto p = getPath(aName);
    if (!p.has_value())
    {
        auto p2 = touchFolder(aName);
        if (p2.has_value())
        {
            temp = p2.value();
        }
    }
    else
    {
        temp = p.value();
    }

    if (!temp.empty())
    {
        std::filesystem::remove_all(temp);
        std::filesystem::create_directories(temp);

        result = true;
        LOG_INFO("Remove folder (", aName, ")");
    }
    else
    {
        LOG_WARNING("Can't remove folder (", aName, ")");
    }

    return result;
}

void
text::Path::addFoldersFrom(const std::string& aPath) noexcept
{
    getInstance().addAllFolders(aPath);
}

void
text::Path::addContentFrom(const std::string& aPath,
                           FileType aFIleType,
                           LevelType aLevelType) noexcept
{

    auto& instance = getInstance();
    auto cont      = getContentMap(aPath, aFIleType, aLevelType);
    for (auto& i : cont)
    {
        instance.mPaths[i.first] = i.second;
    }
}

//--------------------------------------------------------------------------------

std::map<std::string, std::string>
text::Path::getContentMap(const std::string& aPath,
                          FileType aFIleType,
                          LevelType aLevelType) noexcept
{
    std::map<std::string, std::string> result;

    auto paths = getContent(aPath, aFIleType, aLevelType);
    for (auto&& i : paths)
    {
        bool flag = i.back() == '/';
        if (flag) i.pop_back();

        int num = i.size();
        while (num >= 0 && i[num] != '/') num--;
        auto name = i.substr(num + 1, i.size());
        if (flag) i.push_back('/');

        result[name] = std::move(i);
    }

    return result;
}

void
text::Path::addAllFolders(const std::string& aPath) noexcept
{
    auto temp = getContentMap(aPath, FileType::Folder, LevelType::Recursive);
    mPaths.insert(temp.begin(), temp.end());
}

std::vector<std::string>
text::Path::getContent(const std::string& aPath,
                       FileType aFIleType,
                       LevelType aLevelType) noexcept
{
    std::vector<std::string> result;
    if (aLevelType == LevelType::Current)
    {
        result =
            getContent<std::filesystem::directory_iterator>(aPath, aFIleType);
    }
    else
    {
        result = getContent<std::filesystem::recursive_directory_iterator>(
            aPath, aFIleType);
    }
    return result;
}
