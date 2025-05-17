#include "file_read.hpp"

#include <fstream>

#include "core/logging.hpp"

#include "string/separators.hpp"

#include "path.hpp"

//--------------------------------------------------------------------------------

const char*
fs::FileRead::getData(const DataTarget& aTarget) noexcept
{
    return {aTarget.mData};
}

str::String
fs::FileRead::getData(const FilenameRefTarget& aTarget) noexcept
{
    str::String result;
    std::ifstream ios(aTarget.mData);
    if (!ios.is_open())
    {
        LOG_ERROR("No such file (", aTarget.mData, ")");
    }
    else
    {
        std::getline(ios, result, '\0');
        LOG_INFO("Extracting file (", aTarget.mData, ")");
    }
    return result;
}

//--------------------------------------------------------------------------------

std::vector<str::String>
fs::FileRead::getLines(const ReadTarget& aTarget) noexcept
{
    str::String data_storage;
    const str::String* data_ptr = &data_storage;

    switch (aTarget.mType)
    {
        case fs::ReadTarget::DATA:
            data_ptr = &getData(static_cast<const DataTarget&>(aTarget));
            break;
        case fs::ReadTarget::FILE_NAME:
        case fs::ReadTarget::FILE_NAME_REF:
            data_storage =
                getData(static_cast<const FilenameRefTarget&>(aTarget));
            break;
    }
    const char* data = *data_ptr;

    std::vector<str::String> result;
    int last = -1;
    for (int i = 0; i < data.size() + 1; ++i)
    {
        if (str::Separator::newLine(data[i]))
        {
            if (i - last > 1)
            {
                result.emplace_back(data.substr(last + 1, i - last - 1));
            }
            last = i;
        }
    }
    LOG_INFO("Line parsing finished");
    return result;
}

std::vector<std::vector<str::String>>
fs::FileRead::getWords(const ReadTarget& aTarget, FPSeparator aSepFunc) noexcept
{
    auto lines = getLines(aTarget);
    std::vector<std::vector<str::String>> result;
    for (auto& line : lines)
    {
        result.emplace_back();
        // TODO: strtok_r?
        int indx = 0;
        while (indx < line.size())
        {
            while (line.size() > indx && aSepFunc(line[indx])) indx++;
            int from = indx;
            while (line.size() > indx && !aSepFunc(line[indx])) indx++;
            result.back().emplace_back(line.substr(from, indx - from));
            indx += 1;
        }
        if (result.back().empty()) result.pop_back();
    }
    LOG_INFO("Words parsing finished");
    return result;
}

std::unordered_map<str::String, str::String>
fs::FileRead::getWordsMap(const ReadTarget& aTarget,
                          FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aTarget, aSepFunc);
    std::unordered_map<str::String, str::String> result;
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

std::unordered_set<str::String>
fs::FileRead::getWordsSet(const ReadTarget& aTarget,
                          FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aTarget, aSepFunc);
    std::unordered_set<str::String> result;
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
