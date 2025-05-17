#include "to_string.hpp"

// str::String
// dom::ToString::convert(int aData) noexcept
// {
//     return std::to_string(aData);
// }

// str::String
// dom::ToString::convert(size_t aData) noexcept
// {
//     return std::to_string(aData);
// }

// str::String
// dom::ToString::convert(long long aData) noexcept
// {
//     return std::to_string(aData);
// }

// str::String
// dom::ToString::convert(float aData) noexcept
// {
//     return std::to_string(aData);
// }

// str::String
// dom::ToString::convert(double aData) noexcept
// {
//     return std::to_string(aData);
// }

str::String
dom::ToString::convert(bool aData) noexcept
{
    return aData ? "true" : "false";
}

// TODO: return char ptr
str::String
dom::ToString::convert(const char* str) noexcept
{
    return str::String(str);
}
