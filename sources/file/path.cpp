#include "path.hpp"

#include <iostream>

#include "core/program_state.hpp"

#include "file.hpp"

//--------------------------------------------------------------------------------

file::Path::Path() noexcept
{
    reset();
}

file::Path&
file::Path::getInstance() noexcept
{
    static Path instance;
    return instance;
}

void
file::Path::reset() noexcept
{
    auto& state       = core::ProgramState::getInstance();
    mPaths["default"] = state.getWord(core::Word::DEF_PATH);

    auto temp = File::getWords("paths.path");
    for (auto& i : temp)
    {
        mPaths[i[0]] = i[1];
    }

    if (mPaths.empty())
    {
        std::cout << "ERROR: no paths detected!\n";
        exit(0);
    }
}

//--------------------------------------------------------------------------------

std::optional<std::string>
file::Path::getPath(const std::string& aName) noexcept
{
    std::optional<std::string> result;

    auto it = mPaths.find(aName);
    if (it != mPaths.end())
    {
        result = it->second;
    }
    else if ((it = mPaths.find("default")) != mPaths.end())
    {
        result = it->second + aName + "/";
    }

    return result;
}

//--------------------------------------------------------------------------------

std::string
file::Path::getMainPath() noexcept
{
    static std::string globalMainPath = getMainPathOnce();
    return globalMainPath;
}

std::string
file::Path::getExecutablePath() noexcept
{
    static std::string globalExecutablePath = getExecutablePathOnce();
    return globalExecutablePath;
}

//--------------------------------------------------------------------------------

#if defined(BILL_WINDOWS)
#    include <windows.h>
#elif defined(LINUS_LINUX)
#    include <limits.h>
#    include <unistd.h>
#endif

std::string
file::Path::getMainPathOnce() noexcept
{
    std::string path = getExecutablePath();
    do path.pop_back();
    while (path.back() != '\\' && path.back() != '/');
    return path;
}

std::string
file::Path::getExecutablePathOnce() noexcept
{
#if defined(BILL_WINDOWS)
    CHAR buffer[MAX_PATH] = {0};
    uint8_t size          = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    for (int i = 0; i < 1; ++i)
        while (buffer[--size] != L'\\')
            ;
    buffer[size + 1] = 0;
    return std::string(buffer);
#elif defined(LINUS_LINUX)
    char buf[PATH_MAX + 1];
    if (readlink("/proc/self/exe", buf, sizeof(buf) - 1) == -1)
        WRITE_ERROR("readlink() failed");
    std::string str(buf);
    int i = str.size() - 1;
    for (int j = 0; j < 1; --i)
    {
        if (str[i] == '/') ++j;
    }
    return str.substr(0, i + 2);
    // return str.substr(0, str.rfind('/'));
#else
    return "";
#endif
}

//--------------------------------------------------------------------------------
