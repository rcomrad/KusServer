#ifndef PARSER_HPP
#define PARSER_HPP

//--------------------------------------------------------------------------------

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "variable.hpp"

namespace file
{
class Parser
{
public:
    Parser() noexcept = delete;

    static std::optional<Variable> makeVariable(
        const std::string& aStr) noexcept;
    static std::vector<Variable> getVariablesFromFile(
        const std::string aFilename, bool aIsCritical = false) noexcept;

    static std::vector<std::string> slice(
        const std::string& aStr,
        const std::string& aDelimiters,
        const std::string& aErase = "") noexcept;

    enum class Type
    {
        Nun,
        Upper,
        Lower
    };
    static void normalize(std::string& aStr, Type aType) noexcept;
    static std::string normalize(const std::string& aStr, Type aType) noexcept;
};
} // namespace file

//--------------------------------------------------------------------------------

#endif // !PARSER_HPP
