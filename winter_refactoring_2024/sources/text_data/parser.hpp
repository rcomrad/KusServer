#ifndef PARSER_HPP
#define PARSER_HPP

//--------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#include "file.hpp"
#include "variable.hpp"

namespace text
{
class Parser
{
public:
    Parser() noexcept = delete;

    // template <typename T>
    // static std::vector<std::string> slice(T&& aStr,
    //                                       const std::string& aDelimiters,
    //                                       const std::string& aErase) noexcept
    // {
    //     std::unordered_set<char> delimiters(aDelimiters.begin(),
    //                                         aDelimiters.end());
    //     std::unordered_set<char> erase(aErase.begin(), aErase.end());
    //     std::vector<std::string> result(1);

    //     for (auto c : aStr)
    //     {
    //         if (erase.count(c)) continue;
    //         if (delimiters.count(c) && result.back().size())
    //         {
    //             result.emplace_back();
    //             continue;
    //         }

    //         result.back().push_back(c);
    //     }

    //     if (result.back().empty())
    //     {
    //         result.pop_back();
    //     }

    //     return result;
    // }

    // template <typename STR, typename SMBL>
    // static std::vector<std::string> slice(STR&& aStr,
    //                                       SMBL&& aDelimiters,
    //                                       SMBL&& aErase) noexcept
    // {
    //     std::unordered_set<char> delimiters(aDelimiters.begin(),
    //                                         aDelimiters.end());
    //     std::unordered_set<char> erase(aErase.begin(), aErase.end());
    //     std::vector<std::string> result(1);

    //     for (auto c : aStr)
    //     {
    //         if (erase.count(c)) continue;
    //         if (delimiters.count(c) && result.back.size())
    //         {
    //             result.emplace_back();
    //             continue;
    //         }

    //         result.back().emplace_back(c);
    //     }

    //     if (result.back().empty())
    //     {
    //         result.pop_back();
    //     }

    //     return result;
    // }

    static std::optional<Variable> makeVariable(
        const std::string& aStr) noexcept;
    static std::vector<Variable> getVariablesFromFile(
        const std::string& aFilename) noexcept;
    static std::vector<Variable> getVariablesFromFile(
        const std::string& aFolderName, const std::string& aFilename) noexcept;

    static std::vector<std::string> slice(
        const std::string& aStr,
        const std::string& aDelimiters,
        const std::string& aErase = "") noexcept;

    static std::string getFileExtension(const std::string& aFileName) noexcept;

    enum class Type
    {
        Nun,
        Upper,
        Lower
    };
    static void normalize(std::string& aStr, Type aType) noexcept;
    static std::string normalize(const std::string& aStr, Type aType) noexcept;
};
} // namespace text

//--------------------------------------------------------------------------------

#endif // !PARSER_HPP
