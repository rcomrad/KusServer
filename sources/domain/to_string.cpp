#include "to_string.hpp"

const std::string&
dom::toString(const std::string& aStr) noexcept
{
    return aStr;
}

std::string&
dom::toString(std::string& aStr) noexcept
{
    return aStr;
}

std::string&&
dom::toString(std::string&& aStr) noexcept
{
    return std::move(aStr);
}

std::string
dom::toString(const char* c) noexcept
{
    return std::string(c);
}

std::string
dom::toString(int aData) noexcept
{
    return std::to_string(aData);
}

std::string
dom::toString(size_t aData) noexcept
{
    return std::to_string(aData);
}

std::string
dom::toString(long long aData) noexcept
{
    return std::to_string(aData);
}

std::string
dom::toString(float aData) noexcept
{
    return std::to_string(aData);
}

std::string
dom::toString(double aData) noexcept
{
    return std::to_string(aData);
}

std::string
dom::toString(bool aData) noexcept
{
    return aData ? "true" : "false";
}