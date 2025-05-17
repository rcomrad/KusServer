#pragma once

//--------------------------------------------------------------------------------

#include <string_view>
#include <vector>

#include "core/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace kstd
{

class Parser
{
public:
    HOLY_TRINITY_NO_OBJECT(Parser);

    static std::vector<std::string_view> slice(
        const char* buffer,
        const char* aDelimiters) noexcept;
    static std::vector<std::string_view> slice(
        std::string_view,
        const char* aDelimiters) noexcept;

    // std::vector<std::string_view> operator()(char* buffer,
    //                                          const char* aDelimiters,
    //                                          const char* aErase) noexcept;

    // Parser() noexcept = delete;

    // static std::optional<Variable> makeVariable(
    //     const char* aStr) noexcept;
    // static std::vector<Variable> getVariablesFromFile(
    //     const str::String aFilename) noexcept;
    // static std::vector<Variable> getVariablesFromFile(
    //     const char* aFolderName, const str::String aFilename)
    //     noexcept;

    // static std::vector<str::String> slice(
    //     const char* aStr,
    //     const char* aDelimiters,
    //     const char* aErase = "") noexcept;

    // enum class Type
    // {
    //     Nun,
    //     Upper,
    //     Lower
    // };
    // static void normalize(char* aStr, Type aType) noexcept;
    // static str::String normalize(const char* aStr, Type aType)
    // noexcept;
};

} // namespace kstd

//--------------------------------------------------------------------------------
