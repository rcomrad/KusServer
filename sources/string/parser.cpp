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

struct ASCIIBox
{
    int64_t data[2];

    ASCIIBox()
    {
        data[0] = data[1] = 0;
    }

    ASCIIBox(const char* str) : ASCIIBox()
    {
        set(str);
    }

    void set(int8_t num)
    {
        if (num >= 0 && num < 64)
        {
            data[0] |= 1ULL << num;
        }
        else if (num >= 64 && num < 128)
        {
            data[1] |= 1ULL << (num - 64);
        }
        LOG_ERROR("ASCIIBox: num is out of range");
    }

    void set(const char* str)
    {
        while (*str)
        {
            set(static_cast<int8_t>(*str));
            ++str;
        }
    }

    bool get(int8_t num)
    {
        if (num >= 0 && num < 64)
        {
            return data[0] & (1ULL << num);
        } else if (num >= 64 && num < 128)
        {
            return data[1] & (1ULL << (num - 64));
        }
        LOG_ERROR("ASCIIBox: num is out of range");
        return false;
    }
};

std::vector<std::string_view> str::Parser::slice(const std::string_view& aStr,
                                                 char* aWriter,
                                                 const std::string_view& aDelimiters,
                                                 const std::string_view& aErase) noexcept
{
    std::vector<std::string_view> answer;
    ASCIIBox delimiters(aDelimiters.data());
    ASCIIBox erasors(aErase.data());

    auto writer_beg = 0;
    auto writer_end = 0;
    for (const char& sym : aStr)
    {
        if (delimiters.get(sym))
        {
            if (writer_beg != writer_end)
            {
                answer.emplace_back(aWriter + writer_beg, writer_end - writer_beg);
                writer_beg = writer_end;
            }
        }
        else if (!erasors.get(sym))
        {
            aWriter[writer_end] = sym;
            ++writer_end;
        }
    }
    if (writer_beg != writer_end)
    {
        answer.emplace_back(aWriter + writer_beg, writer_end - writer_beg);
    }

    return answer;
}

std::vector<std::string_view> str::Parser::parse_in_current(const std::string_view &aStr,
                                                            const std::string_view &aDelimiters,
                                                            const std::string_view &aErase) noexcept
{
    return slice(aStr, (char*)aStr.data(), aDelimiters, aErase);
}

std::vector<std::string_view> str::Parser::parse_in_new(const std::string_view &aStr,
                                                        char *writer,
                                                        const std::string_view &aDelimiters,
                                                        const std::string_view &aErase) noexcept
{
    return slice(aStr, writer, aDelimiters, aErase);
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
