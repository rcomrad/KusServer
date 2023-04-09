#include "file.hpp"

#include <fstream>
#include <iostream>

file::FileData
file::File::dmpParser(std::string aFileName) noexcept
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
        curArray.name  = name;

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