#pragma once

//------------------------------------------------------------------------------

#include <string>
#include <string_view>

//------------------------------------------------------------------------------

namespace util
{

class Normalize
{
public:
    Normalize() = delete;

    enum class Type
    {
        NUN,
        UPPER,
        LOWER
    };

    static void notation(char* a_str, Type a_type) noexcept;
    static void notation(std::string& a_str, Type a_type) noexcept;
    static void notation(std::string_view a_str, Type a_type) noexcept;
    static std::string notation(const std::string& a_str, Type a_type) noexcept;

    // TODO: refactor for cyrilic
    static bool isUpper(char c) noexcept;
    static bool isLower(char c) noexcept;

    static char toUpper(char c) noexcept;
    static char toLower(char c) noexcept;
};

} // namespace util

//------------------------------------------------------------------------------
