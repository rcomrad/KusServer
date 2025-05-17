#include "kus_string.hpp"

// #undef string

str::String::String() noexcept
{
}

str::String::String(int size) noexcept : std::string(size, '\0')
{
}

str::String::String(const char* s) noexcept : std::string(s)
{
}

// str::String::String(const String& first, const String& second) noexcept
//     : std::string(s)
// {
//     *this = first + second;
// }

char*
str::String::operator=(const char* s) noexcept
{
    return *this;
}

// char*
// str::String::operator=(std::string&& s) noexcept
// {
//     return *this = std::move(s);
// }

const std::string&
str::String::getStdStringRef() const noexcept
{
    return *this;
}

// void
// str::String::addBack(const String& s) noexcept
// {
//     *this += s;
// }

str::String str::String::EMPTY_STRING;
