#include "normalize.hpp"

//------------------------------------------------------------------------------

std::string
util::Normalize::copy(std::string_view a_str, Type a_type) noexcept
{
    std::string result(a_str);
    change(result, a_type);
    return result;
}

void
util::Normalize::change(std::string& a_str, Type a_type) noexcept
{

    bool (*check)(char c) = a_type == Type::UPPER ? isLower : isUpper;
    char (*proc)(char)    = a_type == Type::UPPER ? toUpper : toLower;

    for (auto& c : a_str)
    {
        if (check(c))
        {
            c = proc(c);
        }
    }
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
