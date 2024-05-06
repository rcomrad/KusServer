#include "separators.hpp"

bool
str::Separator::newLine(char c) noexcept
{
    return c == '\n' || c == '\r' || c == '\0';
}

bool
str::Separator::newWord(char c) noexcept
{
    return c == '\t' || c == ' ' || c == ';' || c == '\0';
}

bool
str::Separator::variable(char c) noexcept
{
    return newWord(c) || c == '=';
}

bool
str::Separator::space(char c) noexcept
{
    return c == ' ';
}
