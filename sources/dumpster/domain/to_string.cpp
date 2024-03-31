#include "to_string.hpp"

// std::string
// dom::ToString::convert(int aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// dom::ToString::convert(size_t aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// dom::ToString::convert(long long aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// dom::ToString::convert(float aData) noexcept
// {
//     return std::to_string(aData);
// }

// std::string
// dom::ToString::convert(double aData) noexcept
// {
//     return std::to_string(aData);
// }

std::string
dom::ToString::convert(bool aData) noexcept
{
    return aData ? "true" : "false";
}

// TODO: return char ptr
std::string
dom::ToString::convert(const char* str) noexcept
{
    return std::string(str);
}
