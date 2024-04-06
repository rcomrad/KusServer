#include "file.hpp"

#include <filesystem>
#include <fstream>

#include "path.hpp"

std::string
file::File::getAllData(const std::string& aFileName,
                       file::FileType aFileType) noexcept
{
    std::string result;

    if (aFileType == FileType::File)
    {
        std::ifstream ios(aFileName);
        if (!ios.is_open())
        {

            dom::writeError("No such file (", aFileName, ")");
        }
        else
        {
            dom::writeInfo("Extracting file (", aFileName, ")");
        }

        std::string line;
        while (std::getline(ios, line, '\0'))
        {
            if (line.empty()) continue;
            result += line;
        }
    }
    else
    {
        // TODO: no copy
        dom::writeInfo("Parsing string", aFileName);
        result = aFileName;
    }

    return result;
}

std::string
file::File::getAllData(const std::string& aFolderName,
                       const std::string& aFileName,
                       file::FileType aFileType) noexcept
{
    return pathUnpack(
        static_cast<std::string (*)(const std::string&, file::FileType)>(
            &file::File::getAllData),
        aFolderName, aFileName, aFileType);
}

std::vector<std::string>
file::File::getLines(const std::string& aFileName,
                     file::FileType aFileType) noexcept
{
    std::string temp = getAllData(aFileName, aFileType);
    std::vector<std::string> result;
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
    dom::writeInfo("Lines parsing finished");
    return result;
}

std::vector<std::string>
file::File::getLines(const std::string& aFolderName,
                     const std::string& aFileName,
                     file::FileType aFileType) noexcept
{
    return pathUnpack(
        static_cast<std::vector<std::string> (*)(
            const std::string&, file::FileType)>(&file::File::getLines),
        aFolderName, aFileName, aFileType);
}

std::vector<std::vector<std::string>>
file::File::getWords(const std::string& aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    auto lines = getLines(aFileName, aFileType);
    std::vector<std::vector<std::string>> result;
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
    dom::writeInfo("Words parsing finished");
    return result;
}

std::vector<std::vector<std::string>>
file::File::getWords(const std::string& aFolderName,
                     const std::string& aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<std::vector<std::vector<std::string>> (*)(
            const std::string&, file::FileType, std::function<bool(char)>)>(
            &file::File::getWords),
        aFolderName, aFileName, aFileType, funk);
}

// TODO: merge with getWords
std::unordered_map<std::string, std::string>
file::File::getWordsMap(const std::string& aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    std::unordered_map<std::string, std::string> result;
    auto words = getWords(aFileName, aFileType, funk);

    for (auto& i : words)
    {
        if (i.size() < 2) continue;
        result[i[0]] = i[1];
    }

    return result;
}

std::unordered_map<std::string, std::string>
file::File::getWordsMap(const std::string& aFolderName,
                        const std::string& aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<std::unordered_map<std::string, std::string> (*)(
            const std::string&, file::FileType, std::function<bool(char)>)>(
            &file::File::getWordsMap),
        aFolderName, aFileName, aFileType, funk);
}

std::unordered_set<std::string>
file::File::getWordsSet(const std::string& aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    std::unordered_set<std::string> result;
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

std::unordered_set<std::string>
file::File::getWordsSet(const std::string& aFolderName,
                        const std::string& aFileName,
                        file::FileType aFileType,
                        std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<std::unordered_set<std::string> (*)(
            const std::string&, file::FileType, std::function<bool(char)>)>(
            &file::File::getWordsSet),
        aFolderName, aFileName, aFileType, funk);
}

std::vector<std::unordered_map<std::string, std::string>>
file::File::getTable(const std::string& aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    std::vector<std::unordered_map<std::string, std::string>> result;

    auto words = getWords(aFileName, aFileType, funk);

    // for (auto& i : words)
    // {
    //     std::string gg ;
    //     for (auto& j : i)
    //     {
    //         gg += j + "| ";
    //     }
    //     dom::writeInfo(gg);
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

std::vector<std::unordered_map<std::string, std::string>>
file::File::getTable(const std::string& aFolderName,
                     const std::string& aFileName,
                     file::FileType aFileType,
                     std::function<bool(char)> funk) noexcept
{
    return pathUnpack(
        static_cast<
            std::vector<std::unordered_map<std::string, std::string>> (*)(
                const std::string&, file::FileType, std::function<bool(char)>)>(
            &file::File::getTable),
        aFolderName, aFileName, aFileType, funk);
}

bool
file::File::writeData(const std::string& aFileName,
                      const std::string& aData) noexcept
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
        dom::writeError("Can't create file", aFileName);
    }
    return result;
}

std::optional<std::string>
file::File::writeData(const std::string& aFolderName,
                      const std::string& aFileName,
                      const std::string& aData) noexcept
{
    std::optional<std::string> result;

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
