#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <string_view>
#include <vector>

// #include <unordered_map>
// #include <unordered_set>

//--------------------------------------------------------------------------------

namespace util
{

class Parser
{
    static inline const char* NEW_WORD_SEPARATOR = " \t";

public:
    Parser() noexcept = delete;

    static std::vector<std::string_view> getLinesRef(
        std::string_view a_str) noexcept;
    static std::vector<std::string> getLinesCopy(
        std::string_view a_str) noexcept;

    static std::vector<std::vector<std::string_view>> getWordsRef(
        StringCaster a_str,
        const char* a_separator = NEW_WORD_SEPARATOR) noexcept;
    static std::vector<std::vector<std::string>> getWordsCopy(
        StringCaster a_str,
        const char* a_separator = NEW_WORD_SEPARATOR) noexcept;

    // static std::unordered_map<std::string_view, std::string_view>
    // getWordsMap(
    //     StringCaster a_str,
    //     const char* a_separator = NEW_WORD_SEPARATOR) noexcept;

    // static std::unordered_set<std::string_view> getWordsSet(
    //     StringCaster a_str,
    //     const char* a_separator = NEW_WORD_SEPARATOR) noexcept;
};

} // namespace util

//--------------------------------------------------------------------------------
