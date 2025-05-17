#include "separators.hpp"

bool
kstd::Separator::newLine(char c) noexcept
{
    return c == '\n' || c == '\r' || c == '\0';
}

bool
kstd::Separator::newWord(char c) noexcept
{
    return c == '\t' || c == ' ' || c == ';' || c == '\0';
}

bool
kstd::Separator::variable(char c) noexcept
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
kstd::Separator::space(char c) noexcept
{
    return c == ' ';
}
