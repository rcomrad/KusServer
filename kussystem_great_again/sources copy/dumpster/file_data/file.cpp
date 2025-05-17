#include "file.hpp"

#include <filesystem>
#include <fstream>

#include "path.hpp"

str::String
file::File::getAllData(const char* aFileName, file::FileType aFileType) noexcept
{
    str::String result;

    if (aFileType == FileType::File)
    {
        std::ifstream ios(aFileName);
        if (!ios.is_open())
        {

            LOG_ERROR("No such file (", aFileName, ")");
        }
        else
        {
            LOG_INFO("Extracting file (", aFileName, ")");
        }

        str::String line;
        while (std::getline(ios, line, '\0'))
        {
            if (line.empty()) continue;
            result += line;
        }
    }
    else
    {
        // TODO: no copy
        LOG_INFO("Parsing string", aFileName);
        result = aFileName;
    }

    return result;
}

str::String
file::File::getAllData(const char* aFolderName,
                       const char* aFileName,
                       file::FileType aFileType) noexcept
{
    return pathUnpack(static_cast<str::String (*)(const char*, file::FileType)>(
                          &file::File::getAllData),
                      aFolderName, aFileName, aFileType);
}

std::vector<str::String>
file::File::getLines(const char* aFileName, file::FileType aFileType) noexcept
{
    str::String temp = getAllData(aFileName, aFileType);
    std::vector<str::String> result;
    int last = -1;
    for (int i = 0; i < temp.size() + 1; ++i)
    {
        if (temp[i] == '\n' || temp[i] == '\0')
        {
            if (i - last > 1)
            {
                result.emplace_back(temp.substr(last + 1, i - last - 1));
                // TODO: check or update?
                if (result.back().back() == '\r') result.back().pop_back();
            }
            // last = i + 1;
            last = i;
        }
    }
    LOG_INFO("Lines parsing finished");
    return result;
}

std::vector<str::String>
file::File::getLines(const char* aFolderName,
                     const char* aFileName,
                     file::FileType aFileType) noexcept
{
    return pathUnpack(
        static_cast<std::vector<str::String> (*)(const char*, file::FileType)>(
            &file::File::getLines),
        aFolderName, aFileName, aFileType);
}

std::vector<std::vector<str::String>>
file::File::getWords(const char* aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    auto lines = getLines(aFileName, aFileType);
    std::vector<std::vector<str::String>> result;
    for (auto& line : lines)
    {
        result.emplace_back();
        int indx = 0;
        while (indx < line.size())
        {
            while (line.size() > indx && funk(line[indx])) indx++;
            int from = indx;
            while (line.size() > indx && !funk(line[indx])) indx++;
            result.back().emplace_back(line.substr(from, indx - from));
            indx += 1;
        }
        if (result.back().empty()) result.pop_back();
    }
    LOG_INFO("Words parsing finished");
    return result;
}

std::vector<std::vector<str::String>>
file::File::getWords(const char* aFolderName,
                     const char* aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<std::vector<std::vector<str::String>> (*)(
            const char*, file::FileType, std::function<bool(char)>)>(
            &file::File::getWords),
        aFolderName, aFileName, aFileType, funk);
}

// TODO: merge with getWords
std::unordered_map<str::String, str::String>
file::File::getWordsMap(const char* aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    std::unordered_map<str::String, str::String> result;
    auto words = getWords(aFileName, aFileType, funk);

    for (auto& i : words)
    {
        if (i.size() < 2) continue;
        result[i[0]] = i[1];
    }

    return result;
}

std::unordered_map<str::String, str::String>
file::File::getWordsMap(const char* aFolderName,
                        const char* aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<std::unordered_map<str::String, str::String> (*)(
            const char*, file::FileType, std::function<bool(char)>)>(
            &file::File::getWordsMap),
        aFolderName, aFileName, aFileType, funk);
}

std::unordered_set<str::String>
file::File::getWordsSet(const char* aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    std::unordered_set<str::String> result;
    auto words = getWords(aFileName, aFileType, funk);
    for (auto&& i : words)
    {
        for (auto&& j : i)
        {
            result.insert(std::move(j));
        }
    }
    return result;
}

std::unordered_set<str::String>
file::File::getWordsSet(const char* aFolderName,
                        const char* aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<std::unordered_set<str::String> (*)(
            const char*, file::FileType, std::function<bool(char)>)>(
            &file::File::getWordsSet),
        aFolderName, aFileName, aFileType, funk);
}

std::vector<std::unordered_map<str::String, str::String>>
file::File::getTable(const char* aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    std::vector<std::unordered_map<str::String, str::String>> result;

    auto words = getWords(aFileName, aFileType, funk);

    // for (auto& i : words)
    // {
    //     str::String gg ;
    //     for (auto& j : i)
    //     {
    //         gg += j + "| ";
    //     }
    //     LOG_INFO(gg);
    // }

    for (int i = 1; i < words.size(); ++i)
    {
        auto& temp = result.emplace_back();
        for (int j = 0; j < words[i].size(); ++j)
        {
            temp[words[0][j]] = std::move(words[i][j]);
        }
    }

    return result;
}

std::vector<std::unordered_map<str::String, str::String>>
file::File::getTable(const char* aFolderName,
                     const char* aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<
            std::vector<std::unordered_map<str::String, str::String>> (*)(
                const char*, file::FileType, std::function<bool(char)>)>(
            &file::File::getTable),
        aFolderName, aFileName, aFileType, funk);
}

bool
file::File::writeData(const char* aFileName, const char* aData) noexcept
{
    bool result = false;
    std::ofstream out(aFileName);
    if (out.is_open())
    {
        out << aData;
        out.close();
        result = true;
    }
    else
    {
        LOG_ERROR("Can't create file", aFileName);
    }
    return result;
}

std::optional<str::String>
file::File::writeData(const char* aFolderName,
                      const char* aFileName,
                      const char* aData) noexcept
{
    std::optional<str::String> result;

    auto path = Path::touchFolder(aFolderName);
    if (path.has_value())
    {
        result = path.value() + aFileName;
        writeData(result.value(), aData);
    }

    return result;
}

bool
file::File::isSeparator(char c) noexcept
{
    return c == '\t' || c == ' ' || c == ';' || c == '\0';
}
