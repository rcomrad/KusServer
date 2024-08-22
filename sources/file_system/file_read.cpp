#include "file_read.hpp"

#include <fstream>

#include "core/logging.hpp"

#include "string/separators.hpp"

#include "path.hpp"

//--------------------------------------------------------------------------------

const str::string&
fs::FileRead::getData(const DataTarget& aTarget) noexcept
{
    return {aTarget.mData};
}

std::string
fs::FileRead::getData(const FilenameRefTarget& aTarget) noexcept
{
    return readFile(aTarget.mData);
}

std::string
fs::FileRead::readFile(const str::string& aPath) noexcept
{
    str::string result;
    std::ifstream ios(aPath);
    if (!ios.is_open())
    {
        LOG_ERROR("No such file '%s'", aPath.c_str());
    }
    else
    {
        std::getline(ios, result, '\0');
        LOG_INFO("Extracting file '%s'", aPath.c_str());
    }
    return result;
}

//--------------------------------------------------------------------------------

std::vector<std::string_view>
fs::FileRead::getLines(const ReadTarget& aTarget) noexcept
{
    std::string data_storage;
    const std::string* data_ptr = &data_storage;

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
    const std::string& data = *data_ptr;

    std::vector<std::string_view> result;
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

std::vector<std::vector<std::string_view>>
fs::FileRead::getWords(const ReadTarget& aTarget, FPSeparator aSepFunc) noexcept
{
    auto lines = getLines(aTarget);
    std::vector<std::vector<std::string_view>> result;
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

std::unordered_map<std::string_view, std::string_view>
fs::FileRead::getWordsMap(const ReadTarget& aTarget,
                          FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aTarget, aSepFunc);
    std::unordered_map<std::string_view, std::string_view> result;
    for (auto& i : words)
    {
        if (i.size() != 2)
        {
            LOG_ERROR(
                "An insufficient number of arguments were supplied for map");
        }
        else
        {
            result.insert({i[0], i[1]});
        }
    }

    LOG_INFO("Map creating finished");

    return result;
}

std::unordered_set<std::string_view>
fs::FileRead::getWordsSet(const ReadTarget& aTarget,
                          FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aTarget, aSepFunc);
    std::unordered_set<std::string_view> result;
    for (auto&& i : words)
    {
        for (auto&& j : i)
        {
            result.insert(j);
        }
    }

    LOG_INFO("Set creating finished");

    return result;
}
