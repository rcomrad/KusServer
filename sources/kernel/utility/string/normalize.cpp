#include "normalize.hpp"

//------------------------------------------------------------------------------

std::string
utils::Normalize::copy(std::string_view a_str, Type a_type) noexcept
{
    std::string result(a_str);
    change(result, a_type);
    return result;
}

void
utils::Normalize::change(std::string& a_str, Type a_type) noexcept
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
utils::Normalize::isUpper(char c) noexcept
{
    return std::isupper(c);
}

bool
utils::Normalize::isLower(char c) noexcept
{
    return std::islower(c);
}

char
utils::Normalize::toUpper(char c) noexcept
{
    return std::toupper(c);
}

char
utils::Normalize::toLower(char c) noexcept
{
    return std::tolower(c);
}

//------------------------------------------------------------------------------
