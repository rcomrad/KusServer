#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "core/holy_trinity.hpp"

#include "char_buffer.hpp"
#include "kus_optional.hpp"

//--------------------------------------------------------------------------------

#define HAS_MAP_BY_STR(var, name, size, type) \
    inline static const char name[] = #name;  \
    kstd::HashMapByStr<name, size, type> var;

namespace kstd
{
template <const char* Name, size_t Size, typename ValueType>
class HashMapByStr
{
private:
    CharBuffer<Name, Size> m_key_buffer;
    std::unordered_map<std::string_view, ValueType> m_map;

    using ResultType = decltype(m_map.find("")->second);

public:
    HOLY_TRINITY_SINGLE(HashMapByStr);
    HashMapByStr() noexcept = default;

    auto& operator[](const char* a_key) noexcept
    {
        std::string_view key_view(a_key);
        auto key_it = m_map.find(key_view);
        if (key_it == m_map.end())
        {
            key_view = m_key_buffer.add(a_key);
            key_it   = m_map.emplace(key_view, ValueType()).first;
        }
        return key_it->second;
    }

    auto& operator[](std::string_view key_view) noexcept
    {
        auto key_it = m_map.find(key_view);
        if (key_it == m_map.end())
        {
            key_view = m_key_buffer.add(key_view);
            key_it   = m_map.emplace(key_view, ValueType()).first;
        }
        return key_it->second;
    }

    // TODO: merge gets
    auto get(const char* a_key) const noexcept
    {
        kstd::OptionalValue<const ResultType> result;
        auto it = m_map.find(a_key);
        if (m_map.end() != it)
        {
            result.set(it->second);
        }
        return result;
    }

    auto get(const char* a_key) noexcept
    {
        kstd::OptionalValue<ResultType> result;
        auto it = m_map.find(a_key);
        if (m_map.end() != it)
        {
            result.set(it->second);
        }
        return result;
    }
};
} // namespace kstd

//--------------------------------------------------------------------------------
