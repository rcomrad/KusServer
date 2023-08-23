#include "parser.hpp"

#include "domain/log.hpp"

#include "file.hpp"

std::optional<file::Variable>
file::Parser::makeVariable(const std::string& aStr) noexcept
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

std::vector<file::Variable>
file::Parser::getVariablesFromFile(const std::string aFilename,
                                   bool aIsCritical) noexcept
{
    std::vector<Variable> result;

    auto lines = file::File::getLines(aFilename, aIsCritical);
    for (auto& str : lines)
    {
        auto temp = file::Parser::makeVariable(str);
        if (temp.has_value())
        {
            result.emplace_back(std::move(temp.value()));
        }
        else
        {
            dom::writeError("Line '", str, "' from ", aFilename,
                            " doesn't contain variable");
            continue;
        }
    }

    return result;
}

std::vector<std::string>
file::Parser::slice(const std::string& aStr,
                    const std::string& aDelimiters,
                    const std::string& aErase) noexcept
{
    std::vector<std::string> result(1);

    for (auto i : aStr)
    {
        if (aErase.find(i) != std::string::npos)
        {
            continue;
        }

        if (aDelimiters.find(i) == std::string::npos)
        {
            if (!(std::isspace(i) && result.back().empty()))
            {
                result.back().push_back(i);
            }
        }
        else if (!result.back().empty())
        {
            while (!result.back().empty() && std::isspace(result.back().back()))
            {
                result.back().pop_back();
            }
            result.emplace_back();
        }
    }

    if (!result.empty() && result.back().empty())
    {
        result.pop_back();
    }

    return result;
}

void
file::Parser::normalize(std::string& aStr, Type aType) noexcept
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
file::Parser::normalize(const std::string& aStr, Type aType) noexcept
{
    std::string result = aStr;
    normalize(result, aType);
    return result;
}
