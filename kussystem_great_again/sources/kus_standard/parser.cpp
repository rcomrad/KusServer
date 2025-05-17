#include "parser.hpp"

#include "core/logging.hpp"

#include "separators.hpp"

struct ASCIIBox
{

    uint64_t data[2];

    ASCIIBox()
    {
        data[0] = 0;
        data[1] = 0;
    }
    ASCIIBox(const char* str) : ASCIIBox()
    {
        set(str);
    }

    void set(int num)
    {
        data[0] |= 1 << num;
        data[1] |= 1 << (num - 32);
    }
    void set(const char* str)
    {
        while (*str)
        {
            set(*str);
            ++str;
        }
    }
    bool get(int num)
    {
        return (data[0] & (1 << num)) | (data[1] & (1 << (num - 32)));
    }
};

std::vector<std::string_view>
kstd::Parser::slice(const char* a_buffer, const char* a_delimiters) noexcept
{
    return slice(std::string_view(a_buffer), a_delimiters);
}

std::vector<std::string_view>
kstd::Parser::slice(std::string_view a_buffer,
                    const char* a_delimiters) noexcept
{
    std::vector<std::string_view> result;

    ASCIIBox delimiters(a_delimiters);
    delimiters.set(" \n\t\0");

    auto last = a_buffer.begin();
    auto cur  = --a_buffer.begin();

    do
    {
        ++cur;
        if (delimiters.get(*cur))
        {
            if (0 != last - cur)
            {
                result.emplace_back(cur, last);
            }
            last = cur;
            continue;
        }
    } while (*cur);

    return result;
}

// std::vector<std::string_view>
// kstd::Parser::slice(char* buffer, const char* aDelimiters) noexcept
// {
//     std::vector<std::string_view> result;

//     ASCIIBox delimiters(aDelimiters);
//     delimiters.set(" \n\t\0");

//     const char* last = buffer;
//     const char* cur  = buffer - 1;

//     do
//     {
//         ++cur;
//         if (delimiters.get(*cur))
//         {
//             if (0 != last - cur)
//             {
//                 result.back().emplace_bcak(cur, last);
//             }
//             last = cur;
//             continue;
//         }
//     } while (*cur);

//     return result;
// }

// std::vector<std::string_view>
// kstd::Parser::operator()(char* buffer,
//                          const char* aDelimiters) noexcept
// {
//     std::vector<std::string_view> result(1);

//     ASCIIBox delimiters(aDelimiters);
//     delimiters.set(" \n\t\0");
//     ASCIIBox erase(aErase);

//     const char* last = buffer;
//     const char* cur  = buffer;

//     while (*cur)
//     {
//         if (erase.get(*cur))
//         {
//             continue;
//         }

//         if (delimiters.get(*cur))
//         {
//             if (0 == last - cur)
//             {

//             }
//             continue;
//         }

//         if (aDelimiters.find(i) == str::String::npos)
//         {
//             // TODO: unicode
//             //  if (!(std::isspace(i) && result.back().empty()))
//             if (!(str::Separator::space(i) && result.back().empty()))
//             {
//                 result.back().push_back(i);
//             }
//         }

//         else if (!result.back().empty())
//         {
//             while (!result.back().empty() &&
//                    str::Separator::space(result.back().back()))
//             {
//                 result.back().pop_back();
//             }
//             result.emplace_back();
//         }
//     }

//     if (!result.empty() && result.back().empty())
//     {
//         result.pop_back();
//     }

//     return result;
// }

// #include "file.hpp"

// std::optional<str::Variable>
// str::Parser::makeVariable(const char* aStr) noexcept
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
// str::Parser::getVariablesFromFile(const str::String aFilename) noexcept
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
// str::Parser::getVariablesFromFile(const char* aFolderName,
//                                   const str::String aFilename) noexcept
// {
//     return str::Parser::getVariablesFromFile(
//         core::Path::getFilePathUnsafe(aFolderName, aFilename));
// }

// std::vector<str::String>
// str::Parser::slice(const char* aStr,
//                    const char* aDelimiters,
//                    const char* aErase) noexcept
// {
//     std::vector<str::String> result(1);

//     for (auto i : aStr)
//     {
//         if (aErase.find(i) != str::String::npos)
//         {
//             continue;
//         }

//         if (aDelimiters.find(i) == str::String::npos)
//         {
//             // TODO: unicode
//             //  if (!(std::isspace(i) && result.back().empty()))
//             if (!(str::Separator::space(i) && result.back().empty()))
//             {
//                 result.back().push_back(i);
//             }
//         }
//         else if (!result.back().empty())
//         {
//             while (!result.back().empty() &&
//                    str::Separator::space(result.back().back()))
//             {
//                 result.back().pop_back();
//             }
//             result.emplace_back();
//         }
//     }

//     if (!result.empty() && result.back().empty())
//     {
//         result.pop_back();
//     }

//     return result;
// }

// void
// str::Parser::normalize(char* aStr, Type aType) noexcept
// {
//     if (aType == Type::Upper)
//     {
//         for (auto& i : aStr)
//             if (std::islower(i)) i = std::toupper(i);
//     }
//     else if (aType == Type::Lower)
//     {
//         for (auto& i : aStr)
//             if (std::isupper(i)) i = std::tolower(i);
//     }
// }

// str::String
// str::Parser::normalize(const char* aStr, Type aType) noexcept
// {
//     str::String result;
//    // = aStr;
//     // normalize(result, aType);
//     return result;
// }
