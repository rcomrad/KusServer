#include "file.hpp"

#include <fstream>
#include <iostream>

#include "database/connection_manager.hpp"

#include "path.hpp"

file::FileDataArray
file::File::dmpParser(const std::string& aFileName) noexcept
{
    auto words = File::getWords(aFileName, &file::File::isDMPSeparator);
    file::FileDataArray res;
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

file::FileDataArray
file::File::dataParser(const std::string& aFileName) noexcept
{
    auto words = File::getWords(aFileName);
    file::FileDataArray res;
    for (size_t i = 0; i < words.size(); ++i)
    {
        if (words[i].empty()) continue;
        auto& curArray      = res[words[i][0]];
        int additionalLines = std::stoi(words[i][1]);

        for (++i; i < words.size() && words[i].size() && words[i][0] != "END";
             ++i)
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

std::string
file::File::getAllData(const std::string& aFileName) noexcept
{
    std::ifstream ios(aFileName);
    if (!ios.is_open())
    {
        std::cout << "NO_SUCH_FILE: " + aFileName + "\n";
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
file::File::getLines(const std::string& aFileName) noexcept
{
    std::string temp = getAllData(aFileName);
    std::vector<std::string> result;
    int last = 0;
    for (int i = 0; i < temp.size() + 1; ++i)
    {
        if (temp[i] == '\n' || temp[i] == '\0')
        {
            if (i - last > 1)
            {
                result.emplace_back(temp.substr(last, i - last));
            }
            last = i + 1;
        }
    }
    return result;
}

std::vector<std::vector<std::string>>
file::File::getWords(const std::string& aFileName,
                     decltype(&file::File::isSeparator) funk) noexcept
{
    auto lines = getLines(aFileName);
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
