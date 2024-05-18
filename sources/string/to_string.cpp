#include "to_string.hpp"

#include <cstdio>

void
str::StrPrintf::process(bool aData, char** aPtr) noexcept
{
    *aPtr += std::sprintf(*aPtr, aData ? "true" : "false");
}

void
str::StrPrintf::process(int aData, char** aPtr) noexcept
{
    *aPtr += std::sprintf(*aPtr, "%d", aData);
}

void
str::StrPrintf::process(double aData, char** aPtr) noexcept
{
    *aPtr += std::sprintf(*aPtr, "%lf", aData);
}

void
str::StrPrintf::process(const char* aData, char** aPtr) noexcept
{
    char* cc = (char*)aData;
    *aPtr += std::sprintf(*aPtr, "%s", aData);
}

void
str::StrPrintf::process(const str::string& aData, char** aPtr) noexcept
{
    process(aData.c_str(), aPtr);
}

std::string
str::ToString::convert(bool aData) noexcept
{
    return aData ? "true" : "false";
}

// TODO: return char ptr
std::string
str::ToString::convert(const char* str) noexcept
{
    return std::string(str);
}
