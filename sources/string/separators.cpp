#include "separators.hpp"

bool
str::Separator::isNewLine(char c) noexcept
{
    return c == '\n' || c == '\0' || c == '\r';
}

bool
str::Separator::isNewWord(char c) noexcept
{
    return c == '\t' || c == ' ' || c == ';' || c == '\0';
}
