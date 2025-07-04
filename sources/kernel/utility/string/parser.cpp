#include "parser.hpp"

#include "slicer.hpp"

//--------------------------------------------------------------------------------

std::vector<std::string_view>
util::Parser::getLinesRef(std::string_view a_str) noexcept
{
    return Slicer::change(a_str, "\n\r");
}

std::vector<std::string>
util::Parser::getLinesCopy(std::string_view a_str) noexcept
{
    return Slicer::copy(a_str, "\n\r");
}

std::vector<std::vector<std::string_view>>
util::Parser::getWordsRef(std::string_view a_str,
                          const char* a_separator) noexcept
{
    auto lines = getLinesRef(a_str);
    std::vector<std::vector<std::string_view>> result;
    for (auto& line : lines)
    {
        result.push_back(Slicer::change(line, a_separator));
    }
    return result;
}

std::vector<std::vector<std::string>>
util::Parser::getWordsCopy(std::string_view a_str,
                           const char* a_separator) noexcept
{
    auto lines = getLinesCopy(a_str); // TODO: without copy
    std::vector<std::vector<std::string>> result;
    for (auto& line : lines)
    {
        result.push_back(Slicer::copy(line, a_separator));
    }
    return result;
}

// std::unordered_map<std::string_view, std::string_view>
// util::Parser::getWordsMap(std::string_view  a_str,std::string_view
// a_separator) noexcept
// {
//     auto words = getWords(a_str, a_separator);
//     std::unordered_map<std::string_view, std::string_view> result;
//     for (auto& i : words)
//     {
//         if (i.size() != 2)
//         {
//             LOG_ERROR(
//                 "An insufficient number of arguments were supplied for map");
//         }
//         else
//         {
//             result.insert({i[0], i[1]});
//         }
//     }

//     LOG_INFO("Map creating finished");

//     return result;
// }

// std::unordered_map<std::string_view>
// util::Parser::getWordsMap(std::string_view  a_str,std::string_view
// a_separator) noexcept
// {
//     auto words = getWords(a_str, a_separator);
//     std::unordered_set<std::string_view> result;
//     for (auto& i : words)
//     {
//         for (auto& j : i)
//         {
//             result.insert(j);
//         }
//     }

//     LOG_INFO("Map creating finished");

//     return result;
// }
