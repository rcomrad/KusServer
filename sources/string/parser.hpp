#pragma once

//--------------------------------------------------------------------------------

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "file.hpp"
#include "variable.hpp"

//--------------------------------------------------------------------------------

namespace file
{

class Parser
{
public:
    Parser() noexcept = delete;

    static std::optional<Variable> makeVariable(
        const str::string& aStr) noexcept;
    static std::vector<Variable> getVariablesFromFile(
        const str::string aFilename) noexcept;
    static std::vector<Variable> getVariablesFromFile(
        const str::string& aFolderName, const str::string aFilename) noexcept;

    static std::vector<str::string> slice(
        const str::string& aStr,
        const str::string& aDelimiters,
        const str::string& aErase = "") noexcept;

    enum class Type
    {
        Nun,
        Upper,
        Lower
    };
    static void normalize(str::string& aStr, Type aType) noexcept;
    static str::string normalize(const str::string& aStr, Type aType) noexcept;
};

} // namespace file

//--------------------------------------------------------------------------------
