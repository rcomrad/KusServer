#include "parser.hpp"

#include "core/logging.hpp"

#include "file.hpp"

std::optional<str::Variable>
str::Parser::makeVariable(const str::string& aStr) noexcept
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

std::vector<str::Variable>
str::Parser::getVariablesFromFile(const str::string aFilename) noexcept
{
    std::vector<Variable> result;

    auto lines = file::File::getLines(aFilename);
    for (auto& str : lines)
    {
        auto temp = str::Parser::makeVariable(str);
        if (temp.has_value())
        {
            result.emplace_back(std::move(temp.value()));
        }
        else
        {
            LOG_ERROR("Line '", str, "' from ", aFilename,
                      " doesn't contain variable");
            continue;
        }
    }

    return result;
}

std::vector<str::Variable>
str::Parser::getVariablesFromFile(const str::string& aFolderName,
                                  const str::string aFilename) noexcept
{
    return str::Parser::getVariablesFromFile(
        core::Path::getFilePathUnsafe(aFolderName, aFilename));
}

std::vector<str::string>
str::Parser::slice(const str::string& aStr,
                   const str::string& aDelimiters,
                   const str::string& aErase) noexcept
{
    std::vector<str::string> result(1);

    for (auto i : aStr)
    {
        if (aErase.find(i) != str::string::npos)
        {
            continue;
        }

        if (aDelimiters.find(i) == str::string::npos)
        {
            // TODO: unicode
            //  if (!(std::isspace(i) && result.back().empty()))
            if (!(str::isSpace(i) && result.back().empty()))
            {
                result.back().push_back(i);
            }
        }
        else if (!result.back().empty())
        {
            while (!result.back().empty() && str::isSpace(result.back().back()))
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
str::Parser::normalize(str::string& aStr, Type aType) noexcept
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

str::string
str::Parser::normalize(const str::string& aStr, Type aType) noexcept
{
    str::string result = aStr;
    normalize(result, aType);
    return result;
}
