#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "char_array_buffer.hpp"

//--------------------------------------------------------------------------------

namespace core
{
template <const char* Name, size_t Size, typename ValueType>
struct HashMapByStr
{
public:
    HOLY_TRINITY_SINGLE(HashMapByStr);

    auto& operator[](const char* a_key) noexcept
    {
        std::string_view key_view(a_key);
        auto key_it = m_map.find(key_view);
        if (key_it == m_map.end())
        {
            key_view = m_key_buffer.add(a_key);
            key_it   = m_map.emplace(a_key, {}).first;
        }
        return *key_it;
    }

    auto find(const char* a_key) noexcept
    {
        return m_map.find(a_key);
    }

    auto end() noexcept
    {
        return m_map.end();
    }

private:
    CharArrayBuffer<Name, Size> m_key_buffer;
    std::unordered_map<std::string_view, ValueType> m_map;
};
} // namespace core

//--------------------------------------------------------------------------------
