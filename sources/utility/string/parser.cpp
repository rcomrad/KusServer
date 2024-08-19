#include "parser.hpp"

#include "core/logging/logging.hpp"

#include "slicer.hpp"

//--------------------------------------------------------------------------------

std::vector<std::string_view>
util::Parser::getLines(StringCaster a_str) noexcept
{
    LOG_INFO("Parsing lines");
    return Slicer::process(a_str, "\n\r");
}

std::vector<std::vector<std::string_view>>
util::Parser::getWords(StringCaster a_str, const char* a_separator) noexcept
{
    auto lines = getLines(a_str);
    std::vector<std::vector<std::string_view>> result;
    for (auto& line : lines)
    {
        result.push_back(Slicer::process(line, a_separator));
    }
    LOG_INFO("Words parsing finished");
    return result;
}

std::unordered_map<std::string_view, std::string_view>
util::Parser::getWordsMap(StringCaster a_str, const char* a_separator) noexcept
{
    auto words = getWords(a_str, a_separator);
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
util::Parser::getWordsSet(StringCaster a_str, const char* a_separator) noexcept
{
    auto words = getWords(a_str, a_separator);
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
