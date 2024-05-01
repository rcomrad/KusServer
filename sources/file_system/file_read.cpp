#include <fstream>

#include "core/logging.hpp"
#include "string/separators.hpp"

#include "file_reader.hpp"
#include "path.hpp"

fs::ReadResult
fs::FileRead::getData(const ReadTarget& aTarget) noexcept
{
    ReadResult result;

    switch (aTarget.mType)
    {
        case ReadTarget::Type::DATA:
            result.mDataRef     = &aTarget.mData;
            result.mIsDataInRef = true;
            break;

        case ReadTarget::Type::FILE_NAME:
            result.mData        = readFile(aTarget.mFileName);
            result.mIsDataInRef = false;
            break;

        case ReadTarget::Type::FILE_LOCATION:
            auto path =
                Path::getFilePath(aTarget.mFolderName, aTarget.mFileName);

            if (path.has_value())
            {
                result.mData = readFile(path.value());
            }
            else
            {
                LOG_ERROR("Can't find file (Name:", aTarget.mFileName,
                          "Folder:", aTarget.mFileName, ")");
            }
            result.mIsDataInRef = false;

            break;
    }

    return result;
}

str::string
fs::FileRead::readFile(const str::string& aPath) noexcept
{
    str::string result;
    std::ifstream ios(aPath);
    if (!ios.is_open())
    {
        LOG_ERROR("No such file (", aPath, ")");
    }
    else
    {
        std::getline(ios, result, '\0');
        LOG_INFO("Extracting file (", aPath, ")");
    }
    return result;
}

std::vector<std::string>
fs::FileRead::getLines(const ReadTarget& aTarget) noexcept
{
    auto temp                  = getData(aTarget);
    const str::string* datePtr = temp.mDataRef;
    if (!temp.mIsDataInRef)
    {
        datePtr = &temp.mData;
    }
    const str::string& dateRef = *datePtr;

    std::vector<std::string> result;
    int last = -1;
    for (int i = 0; i < dateRef.size() + 1; ++i)
    {
        if (str::Separator::isNewLine(dateRef[i]))
        {
            if (i - last > 1)
            {
                result.emplace_back(dateRef.substr(last + 1, i - last - 1));
            }
            last = i;
        }
    }
    LOG_INFO("Line parsing finished");
    return result;
}

std::vector<std::vector<std::string>>
file::FileRead::getWords(const ReadTarget& aTarget,
                         FPSeparator aSepFunc) noexcept
{
    auto lines = getLines(aFileName, aFileType);
    std::vector<std::vector<std::string>> result;
    for (auto& line : lines)
    {
        result.emplace_back();
        // TODO: strtok_r?
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

std::unordered_map<std::string, std::string>
file::FileRead::getWordsMap(const ReadTarget& aTarget,
                            FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aTarget, aSepFunc);
    std::unordered_map<std::string, std::string> result;
    for (auto& i : words)
    {
        if (i.size() != 2)
        {
            LOG_ERROR(
                "An insufficient number of arguments were supplied for map");
        }
        else
        {
            result.insert({std::move(i[0]), std::move(i[1])});
        }
    }

    LOG_INFO("Map creating finished");

    return result;
}

std::unordered_set<std::string>
file::FileRead::getWordsSet(const ReadTarget& aTarget,
                            FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aTarget, aSepFunc);
    std::unordered_set<std::string> result;
    for (auto&& i : words)
    {
        for (auto&& j : i)
        {
            result.insert(std::move(j));
        }
    }

    LOG_INFO("Set creating finished");

    return result;
}
