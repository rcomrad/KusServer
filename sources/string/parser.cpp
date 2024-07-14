#include "parser.hpp"

#include "core/logging.hpp"

#include "string/separators.hpp"

// #include "file.hpp"

// std::optional<str::Variable>
// str::Parser::makeVariable(const str::string& aStr) noexcept
// {
//     std::optional<Variable> result;

//     auto parts = slice(aStr, "=");
//     if (parts.size() == 2)
//     {
//         Variable temp;
//         temp.name      = parts[0];
//         temp.value.str = parts[1];
//         normalize(temp.name, Type::Lower);
//         result = std::move(temp);
//     }

//     return result;
// }

// std::vector<str::Variable>
// str::Parser::getVariablesFromFile(const str::string aFilename) noexcept
// {
//     std::vector<Variable> result;

//     auto lines = file::File::getLines(aFilename);
//     for (auto& str : lines)
//     {
//         auto temp = str::Parser::makeVariable(str);
//         if (temp.has_value())
//         {
//             result.emplace_back(std::move(temp.value()));
//         }
//         else
//         {
//             LOG_ERROR("Line '", str, "' from ", aFilename,
//                       " doesn't contain variable");
//             continue;
//         }
//     }

//     return result;
// }

// std::vector<str::Variable>
// str::Parser::getVariablesFromFile(const str::string& aFolderName,
//                                   const str::string aFilename) noexcept
// {
//     return str::Parser::getVariablesFromFile(
//         core::Path::getFilePathUnsafe(aFolderName, aFilename));
// }

std::vector<std::string_view>
str::Parser::slice(const std::string_view& aStr,
                   const str::string& aDelimiters,
                   const str::string& aErase) noexcept
{
    std::vector<std::string_view> result;
    size_t start    = 0;
    size_t char_pos = 0;

    auto is_erase_char = [&](char c)
    { return aErase.find(c) != str::string::npos; };

    auto is_delimiter_char = [&](char c)
    { return aDelimiters.find(c) != str::string::npos; };

    for (char c : aStr)
    {
        if (is_erase_char(c))
        {
            continue;
        }

        if (!is_delimiter_char(c))
        {
            if (!(str::Separator::space(c) && char_pos == 0))
            {
                ++char_pos;
            }
        }
        else if (char_pos > 0)
        {
            while (char_pos > 0 &&
                   str::Separator::space(aStr[start + char_pos - 1]))
            {
                --char_pos;
            }
            result.emplace_back(aStr.data() + start, char_pos);
            start += char_pos + 1;
            char_pos = 0;
        }
        else
        {
            ++start;
        }
    }

    if (char_pos > 0)
    {
        while (char_pos > 0 &&
               str::Separator::space(aStr[start + char_pos - 1]))
        {
            --char_pos;
        }
        if (char_pos > 0)
        {
            result.emplace_back(aStr.data() + start, char_pos);
        }
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
