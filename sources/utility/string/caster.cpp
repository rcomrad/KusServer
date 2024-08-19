#include "caster.hpp"

util::StringCaster::StringCaster(char* a_str) noexcept
    : m_is_stroes_size(false), m_str_ptr(a_str)
{
}

util::StringCaster::StringCaster(std::string& a_str) noexcept
    : m_is_stroes_size(true),
      m_str_size(a_str.size()),
      m_str_ptr(const_cast<char*>(a_str.data()))
{
}

util::StringCaster::StringCaster(std::string_view a_str) noexcept
    : m_is_stroes_size(true),
      m_str_size(a_str.size()),
      m_str_ptr(const_cast<char*>(a_str.data()))
{
}

char*
util::StringCaster::obtain() noexcept
{
    return m_str_ptr;
}

char*
util::StringCaster::obtain(size_t a_min_size) noexcept
{
    if (m_is_stroes_size && a_min_size < m_str_size)
    {
        return nullptr;
    }
    return m_str_ptr;
}

char*
util::StringCaster::obtain(StringCaster a_min_size) noexcept
{
    if (a_min_size.m_is_stroes_size)
    {
        return obtain(a_min_size.m_str_size);
    }
    return m_str_ptr;
}
