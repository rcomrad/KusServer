#include "parser.hpp"

#include <unordered_set>

#include "text_data/cyrillic.hpp"

#include "general_tools/log.hpp"

#include "file.hpp"

std::optional<text::Variable>
text::Parser::makeVariable(const std::string& aStr) noexcept
{
    std::optional<Variable> result;

    auto parts = slice(aStr, "=");
    if (parts.size() == 2)
    {
        Variable temp;
        temp.name      = parts[0];
        temp.value.str = parts[1];
        normalize(temp.name, Type::Lower);
        result = std::move(temp);
    }

    return result;
}

std::vector<text::Variable>
text::Parser::getVariablesFromFile(const std::string& aFileName) noexcept
{
    std::vector<Variable> result;

    auto lines = text::File::getLines(aFileName);
    for (auto& str : lines)
    {
        auto temp = text::Parser::makeVariable(str);
        if (temp.has_value())
        {
            result.emplace_back(std::move(temp.value()));
        }
        else
        {
            LOG_ERROR("Line '", str, "' from ", aFileName,
                      " doesn't contain variable");
            continue;
        }
    }

    return result;
}

std::string
text::Parser::getFileExtension(const std::string& aFileName) noexcept
{
    int indx = aFileName.size() - 1;
    while (aFileName[indx] != '.') --indx;
    return aFileName.substr(indx + 1);
}

std::vector<text::Variable>
text::Parser::getVariablesFromFile(const std::string& aFolderName,
                                   const std::string& aFilename) noexcept
{
    return text::Parser::getVariablesFromFile(
        text::Path::getPathUnsafe(aFolderName, aFilename));
}

std::vector<std::string>
text::Parser::slice(const std::string& aStr,
                    const std::string& aDelimiters,
                    const std::string& aErase) noexcept
{
    std::unordered_set<char> delimiters(aDelimiters.begin(), aDelimiters.end());
    std::unordered_set<char> erase(aErase.begin(), aErase.end());
    std::vector<std::string> result(1);

    for (auto c : aStr)
    {
        if (erase.count(c)) continue;
        if (delimiters.count(c) && result.back().size())
        {
            result.emplace_back();
            continue;
        }

        result.back().push_back(c);
    }

    if (result.back().empty())
    {
        result.pop_back();
    }

    return result;
}

void
text::Parser::normalize(std::string& aStr, Type aType) noexcept
{
    if (aType == Type::Upper)
    {
        for (auto& i : aStr)
            if (std::islower(i)) i = std::toupper(i);
    }
    else if (aType == Type::Lower)
    {
        for (auto& i : aStr)
            if (std::isupper(i)) i = std::tolower(i);
    }
}

std::string
text::Parser::normalize(const std::string& aStr, Type aType) noexcept
{
    std::string result = aStr;
    normalize(result, aType);
    return result;
}
