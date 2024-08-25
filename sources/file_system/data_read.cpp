#include "data_read.hpp"

#include <fstream>

#include "core/logging.hpp"

#include "string/separators.hpp"

//--------------------------------------------------------------------------------

str::string
fs::DataRead::readFile(const str::string& aPath) noexcept
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
fs::DataRead::getLines(const std::string_view& aData) noexcept
{
    std::vector<std::string_view> result;
    auto start = aData.begin();
    while (start != aData.end())
    {
        auto end = std::find(start, aData.end(), '\n');
        result.emplace_back(&*start, std::distance(start, end));
        start = end != aData.end() ? end + 1 : aData.end();
    }
    LOG_INFO("Line parsing finished");
    return result;
}

std::vector<std::vector<std::string_view>>
fs::DataRead::getWords(const std::string_view& aData, FPSeparator aSepFunc) noexcept
{
    auto lines = getLines(aData);
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
            result.back().emplace_back(&line[from], indx - from);
            indx += 1;
        }
        if (result.back().empty()) result.pop_back();
    }
    LOG_INFO("Words parsing finished");
    return result;
}

std::unordered_map<std::string_view, std::string_view>
fs::DataRead::getWordsMap(const std::string_view& aData,
                          FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aData, aSepFunc);
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
fs::DataRead::getWordsSet(const std::string_view& aData,
                          FPSeparator aSepFunc) noexcept
{
    auto words = getWords(aData, aSepFunc);
    std::unordered_set<std::string_view> result;
    for (auto& i : words)
    {
        for (auto& j : i)
        {
            result.insert(j);
        }
    }

    LOG_INFO("Set creating finished");

    return result;
}
