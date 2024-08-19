#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <string_view>
#include <vector>

//--------------------------------------------------------------------------------

namespace util
{

class StringCaster
{
public:
    StringCaster(char* a_str) noexcept;
    StringCaster(std::string& a_str) noexcept;
    StringCaster(std::string_view a_str) noexcept;

    char* obtain() noexcept;
    char* obtain(size_t a_min_size) noexcept;
    char* obtain(StringCaster a_min_size) noexcept;

private:
    bool m_is_stroes_size;
    size_t m_str_size;
    char* m_str_ptr;
};

} // namespace util

//--------------------------------------------------------------------------------
