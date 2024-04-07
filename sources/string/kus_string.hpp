#pragma once

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace str
{

using string = std::string;
static string EMPTY_STRING;

bool
isSpace(char c)
{
    return std::isspace(c);
}

} // namespace str

//--------------------------------------------------------------------------------
