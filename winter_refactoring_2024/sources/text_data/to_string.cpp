#include "to_string.hpp"

// std::string
// text::ToString::convert(int aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// text::ToString::convert(size_t aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// text::ToString::convert(long long aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// text::ToString::convert(float aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// text::ToString::convert(double aData) noexcept
// {
//     return std::to_string(aData);
// }

std::string
text::ToString::convert(bool aData) noexcept
{
    return aData ? "true" : "false";
}

// TODO: return char ptr
std::string
text::ToString::convert(const char* str) noexcept
{
    return std::string(str);
}
