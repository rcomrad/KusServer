#pragma once

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace str
{

typedef string std::string;
static string EMPTY_STRING = "";

isEmptyString(str::string aStr)
{
    return aStr.empty();
}

} // namespace str

//--------------------------------------------------------------------------------
