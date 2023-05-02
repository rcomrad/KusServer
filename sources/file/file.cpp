#include "file.hpp"

#include <fstream>
#include <iostream>

#include "database/connection_manager.hpp"

#include "path.hpp"

data::RawDataArray
file::File::dmpParser(const std::string& aFileName) noexcept
{
    auto words = File::getWords(aFileName, false, &file::File::isDMPSeparator);
    data::RawDataArray res;
    for (size_t i = 0; i < words.size(); ++i)
    {
        if (words[i].empty()) continue;
        auto& curArray = res[words[i][0]];

        for (++i; i < words.size() && words[i].size() && words[i][0] != "END";
             ++i)
        {
            curArray.value.emplace_back(std::move(words[i]));
        }
    }
    return res;
}

data::RawDataArray
file::File::dataParser(const std::string& aFileName) noexcept
{
    auto words = File::getWords(aFileName);
    data::RawDataArray res;
    for (size_t i = 0; i < words.size(); ++i)
    {
        if (words[i].empty()) continue;
        auto& curArray      = res[words[i][0]];
        int additionalLines = std::stoi(words[i][1]);

        for (i += 2;
             i < words.size() && words[i].size() && words[i][0] != "END"; ++i)
        {
            curArray.value.emplace_back(std::move(words[i]));
            for (int j = 0; j < additionalLines; ++j)
            {
                curArray.additionalInfo.emplace_back(std::move(words[++i]));
            }
        }
    }
    return res;
}

data::RawDataArray
file::File::csvParser(const std::string& aFileName) noexcept
{
    auto words = File::getWords(aFileName, false, &file::File::isCSVSeparator);
    data::RawDataArray res;
    auto& curArray = res["data"];
    words[0].clear();
    for (auto& i : words)
    {
        if (i.empty()) continue;
        curArray.value.emplace_back(std::move(i));
    }
    return res;
}

std::string
file::File::getAllData(const std::string& aFileName, bool aIsCritical) noexcept
{
    std::ifstream ios(aFileName);
    if (!ios.is_open())
    {
        std::cout << "NO_SUCH_FILE: " + aFileName + "\n";
        if (aIsCritical) exit(0);
    }
    else
    {
        std::cout << "Extracting_file: " + aFileName + "\n";
    }

    std::string result;
    std::string line;
    while (std::getline(ios, line, '\0'))
    {
        if (line.empty()) continue;
        result += line;
    }
    return result;
}

std::vector<std::string>
file::File::getLines(const std::string& aFileName, bool aIsCritical) noexcept
{
    std::string temp = getAllData(aFileName, aIsCritical);
    std::vector<std::string> result;
    int last = 0;
    for (int i = 0; i < temp.size() + 1; ++i)
    {
        if (temp[i] == '\n' || temp[i] == '\0')
        {
            if (i - last > 1)
            {
                result.emplace_back(temp.substr(last, i - last));
                // TODO: check or update?
                if (result.back().back() == '\r') result.back().pop_back();
            }
            last = i + 1;
        }
    }
    return result;
}

std::vector<std::vector<std::string>>
file::File::getWords(const std::string& aFileName,
                     bool aIsCritical,
                     decltype(&file::File::isSeparator) funk) noexcept
{
    auto lines = getLines(aFileName, aIsCritical);
    std::vector<std::vector<std::string>> result;
    for (auto& line : lines)
    {
        result.emplace_back();
        int indx = 0;
        while (indx < line.size())
        {
            while (funk(line[indx])) indx++;
            int from = indx;
            while (!funk(line[indx])) indx++;
            result.back().emplace_back(line.substr(from, indx - from));
            indx += 1;
        }
    }
    return result;
}

std::vector<std::array<std::string, 2>>
file::File::getMap(const std::string& aFileName, bool aIsCritical) noexcept
{
    auto lines = getLines(aFileName, aIsCritical);
    static std::vector<std::array<std::string, 2>> result;
    for (auto& line : lines)
    {
        result.emplace_back();
        int indx = 0;

        while (isSeparator(line[indx])) indx++;
        int from = indx;
        while (!isSeparator(line[indx])) indx++;
        result.back()[0] = line.substr(from, indx - from);

        while (isSeparator(line[indx])) indx++;
        result.back()[1] = line.substr(indx);
    }
    return result;
}

bool
file::File::isSeparator(char c) noexcept
{
    return c == '\t' || c == ' ' || c == ';' || c == '\0';
}

bool
file::File::isDMPSeparator(char c) noexcept
{
    return c == '\t' || c == ';' || c == '\0';
}

bool
file::File::isCSVSeparator(char c) noexcept
{
    return c == ';' || c == '\0';
}

std::string
file::File::getAllWithBr(const std::string& aFileName) noexcept
{
    auto temp = getLines(aFileName);
    std::string result;
    for (auto& i : temp)
    {
        result += i + "<br>";
    }
    return result;
}

std::string
file::File::writeData(const std::string& aFolderName,
                      const std::string& aFileName,
                      const std::string& aData) noexcept
{
    std::string resultFileName = "NUN";

    auto path = Path::getInstance().getPath(aFolderName);
    if (!path)
    {
        std::cout << "ERROR: no_such_folder " << aFolderName << "\n";
        path = Path::getInstance().getPath("upload");
    }

    if (path)
    {
        std::string pathPrefix = path.value();
        std::string filePath;
        {
            auto connection = data::ConnectionManager::getUserConnection();
            auto table      = connection.val.getData<data::File>();
            resultFileName  = std::to_string(table.num++) + "-" + aFileName;
            filePath        = pathPrefix + resultFileName;
            connection.val.update<data::File>(table);
        }
        std::ofstream out(filePath);
        out << aData;
        out.close();
    }
    else
    {
        std::cout << "ERROR: no_upload_folder\n";
    }

    return resultFileName;
}
