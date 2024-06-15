#pragma once

//--------------------------------------------------------------------------------

#include <functional>
#include <optional>
#include <unordered_map>
#include <vector>

#include "core/holy_trinity.hpp"

#include "kus_string.hpp"
#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace str
{

class Parser
{
public:
    HOLY_TRINITY_NO_OBJECT(Parser);

    std::vector<std::string_view> operator()(const char* buffer,
                                             const char* aDelimiters,
                                             const char* aErase = "") noexcept;

    // Parser() noexcept = delete;

    // static std::optional<Variable> makeVariable(
    //     const str::String& aStr) noexcept;
    // static std::vector<Variable> getVariablesFromFile(
    //     const str::String aFilename) noexcept;
    // static std::vector<Variable> getVariablesFromFile(
    //     const str::String& aFolderName, const str::String aFilename)
    //     noexcept;

    // static std::vector<str::String> slice(
    //     const str::String& aStr,
    //     const str::String& aDelimiters,
    //     const str::String& aErase = "") noexcept;

    // enum class Type
    // {
    //     Nun,
    //     Upper,
    //     Lower
    // };
    // static void normalize(str::String& aStr, Type aType) noexcept;
    // static str::String normalize(const str::String& aStr, Type aType)
    // noexcept;
};

} // namespace str

//--------------------------------------------------------------------------------
