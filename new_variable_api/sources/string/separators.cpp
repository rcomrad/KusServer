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
    static bool commentFlag = false;
    if (c == '#')
    {
        commentFlag = true;
    }
    if (newLine(c))
    {
        commentFlag = false;
    }

    bool result = true;
    if (!commentFlag)
    {
        result = newWord(c) || c == '=';
    }
    return result;
}

bool
str::Separator::space(char c) noexcept
{
    return c == ' ';
}
