#include "normalize.hpp"

//------------------------------------------------------------------------------

void
util::Normalize::notation(char* a_str, Type a_type) noexcept
{
    bool (*check)(char c) = a_type == Type::UPPER ? isLower : isUpper;
    char (*proc)(char)    = a_type == Type::UPPER ? toUpper : toLower;

    while (*a_str)
    {
        if (check(*a_str))
        {
            *a_str = proc(*a_str);
        }
        ++a_str;
    }
}

void
util::Normalize::notation(std::string& a_str, Type a_type) noexcept
{
    notation(a_str.data(), a_type);
}

void
util::Normalize::notation(std::string_view a_str, Type a_type) noexcept
{
    notation(const_cast<char*>(a_str.data()), a_type);
}

std::string
util::Normalize::notation(const std::string& a_str, Type a_type) noexcept
{
    std::string result = a_str;
    notation(result, a_type);
    return result;
}

//------------------------------------------------------------------------------

bool
util::Normalize::isUpper(char c) noexcept
{
    return std::isupper(c);
}

bool
util::Normalize::isLower(char c) noexcept
{
    return std::islower(c);
}

char
util::Normalize::toUpper(char c) noexcept
{
    return std::toupper(c);
}

char
util::Normalize::toLower(char c) noexcept
{
    return std::tolower(c);
}

//------------------------------------------------------------------------------
