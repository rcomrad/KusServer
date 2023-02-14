#include "file_reader.hpp"

dom::FileReader::FileReader(const std::string& aFileName) noexcept
    : mInp(aFileName)
{
}

dom::FileReader::~FileReader()
{
    this->close();
}

std::vector<std::string>
dom::FileReader::getAllStrings(const std::string& aFileName) noexcept
{
    std::ifstream file(aFileName);
    std::vector<std::string> result;
    std::string temp;
    while (getline(file, temp))
        result.emplace_back(std::move(temp));
    file.close();
    return result;
}

void
dom::FileReader::close() noexcept
{
    mInp.close();
}
