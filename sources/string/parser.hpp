#pragma once

//--------------------------------------------------------------------------------

#include <functional>
#include <optional>
#include <unordered_map>
#include <vector>

#include "kus_string.hpp"
#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace str
{

class Parser
{
public:
    Parser() noexcept = delete;

    // static std::optional<Variable> makeVariable(
    //     const str::string& aStr) noexcept;
    // static std::vector<Variable> getVariablesFromFile(
    //     const str::string aFilename) noexcept;
    // static std::vector<Variable> getVariablesFromFile(
    //     const str::string& aFolderName, const str::string aFilename)
    //     noexcept;

    static std::vector<std::string_view> slice(
        const std::string_view& aStr,
        char* aWriter,
        const std::string_view& aDelimiters,
        const std::string_view& aErase = "") noexcept;

    enum class Type
    {
        Nun,
        Upper,
        Lower
    };
    static void normalize(str::string& aStr, Type aType) noexcept;
    static str::string normalize(const str::string& aStr, Type aType) noexcept;
};

} // namespace str

//--------------------------------------------------------------------------------
