#pragma once

//--------------------------------------------------------------------------------

#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "caster.hpp"

//--------------------------------------------------------------------------------

#define NEW_WORD_SEPARATOR " \t"

namespace util
{

class Parser
{
public:
    Parser() noexcept = delete;

    static std::vector<std::string_view> getLines(StringCaster a_str) noexcept;

    static std::vector<std::vector<std::string_view>> getWords(
        StringCaster a_str,
        const char* a_separator = NEW_WORD_SEPARATOR) noexcept;

    static std::unordered_map<std::string_view, std::string_view> getWordsMap(
        StringCaster a_str,
        const char* a_separator = NEW_WORD_SEPARATOR) noexcept;

    static std::unordered_set<std::string_view> getWordsSet(
        StringCaster a_str,
        const char* a_separator = NEW_WORD_SEPARATOR) noexcept;
};

#undef NEW_WORD_SEPARATOR

} // namespace util

//--------------------------------------------------------------------------------
