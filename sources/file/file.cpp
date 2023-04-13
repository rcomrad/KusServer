#include "file.hpp"

#include <fstream>
#include <iostream>

file::FileData
file::File::dmpParser(const std::string& aFileName) noexcept
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

    file::FileData res;

    std::string name;
    while (std::getline(ios, name))
    {
        if (name.empty()) continue;
        auto& curArray = res.data[name];

        std::string row;
        while (std::getline(ios, row) && row != "END")
        {
            curArray.value.emplace_back();
            int indx = 0;
            while (indx < row.size())
            {
                while (row[indx] == '\t') indx++;
                int from = indx;
                while (row[indx] != ';' && row[indx] != '\0') indx++;
                curArray.value.back().emplace_back(
                    row.substr(from, indx - from));
                indx += 1;
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
file::File::getWords(const std::string& aFileName) noexcept
{
    auto lines = getLines(aFileName);
    std::vector<std::vector<std::string>> result;
    for (auto& line : lines)
    {
        result.emplace_back();
        int indx = 0;
        while (indx < line.size())
        {
            while (isSeparator(line[indx])) indx++;
            int from = indx;
            while (!isSeparator(line[indx])) indx++;
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
