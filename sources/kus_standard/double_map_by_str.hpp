#pragma once

//--------------------------------------------------------------------------------

#include <type_traits>
#include <unordered_map>

#include "core/holy_trinity.hpp"
#include "core/logging.hpp"

#include "char_buffer.hpp"
#include "kus_optional.hpp"

//--------------------------------------------------------------------------------

namespace kstd
{
template <const char* Name, size_t Size, typename ValueType>
class DoubleMapByStr
{
private:
    using inner_valure = std::unordered_map<std::string_view, ValueType>;
    class MapNode
    {
    public:
        HOLY_TRINITY_NO_RELEASE_COPY(MapNode);

        ValueType& operator[](const char* a_key) noexcept
        {
            std::string_view key_view(a_key);
            auto key_it = m_cur_cell->second.find(key_view);
            if (key_it == m_cur_cell->second.end())
            {
                key_view = m_this->m_key_buffer.add(a_key);
                key_it =
                    m_cur_cell->second.emplace(key_view, ValueType()).first;
            }
            return key_it->second;
        }

    private:
        MapNode(DoubleMapByStr* a_ptr, inner_valure::iterator a_iter)
            : m_this(a_ptr), m_cur_cell(a_iter)
        {
        }

        DoubleMapByStr* m_this;
        inner_valure::iterator m_cur_cell;
    };

public:
    HOLY_TRINITY_SINGLE(DoubleMapByStr);
    DoubleMapByStr() noexcept = default;

    MapNode operator[](const char* a_key) noexcept
    {
        std::string_view key_view(a_key);
        auto key_it = m_map.find(key_view);
        if (key_it == m_map.end())
        {
            key_view = m_key_buffer.add(a_key);
            key_it   = m_map.emplace(key_view, {}).first;
        }
        return MapNode(this, key_it);
    }

    auto get(const char* a_key_volume) noexcept
    {
        return inner_get<DoubleMapByStr*>(this, a_key_volume);
    }

    auto get(const char* a_key_volume) const noexcept
    {
        return inner_get<const DoubleMapByStr*>(this, a_key_volume);
    }

    auto get(const char* a_key_volume, const char* a_key_node) noexcept
    {
        return inner_get<DoubleMapByStr*>(this, a_key_volume, a_key_node);
    }

    auto get(const char* a_key_volume, const char* a_key_node) const noexcept
    {
        return inner_get<const DoubleMapByStr*>(this, a_key_volume, a_key_node);
    }

private:
    CharBuffer<Name, Size> m_key_buffer;
    std::unordered_map<std::string_view, inner_valure> m_map;

    template <typename ClassThisType>
    static auto inner_get(ClassThisType a_this,
                          const char* a_key_volume) noexcept
    {
        // TODO: move to metaprogramming
        using DefaultResult =
            decltype(a_this->m_map.find(a_key_volume)->second);
        DefaultResult aaa;
        using IsConstResultT = std::is_const<ClassThisType>;
        using FinalResult =
            std::conditional<IsConstResultT::value, const DefaultResult,
                             DefaultResult>::type;

        // kstd::OptionalPtr<FinalResult> result;
        kstd::OptionalPtr<inner_valure> result;

        auto it_volume = a_this->m_map.find(a_key_volume);
        if (a_this->m_map.end() != it_volume)
        {
            result.set(&it_volume->second);
        }
        else
        {
            LOG_ERROR("No such callback volume (", a_key_volume, ")");
        }

        return result;
    }

    template <typename ClassThisType>
    static auto inner_get(ClassThisType a_this,
                          const char* a_key_volume,
                          const char* a_key_node) noexcept
    {
        // TODO: move to metaprogramming
        // using IsConstResultT = std::is_const<ClassThisType>;
        // using FinalResult =
        //     std::conditional<IsConstResultT::value,
        //                      std::add_const<ValueType>::type,
        //                      ValueType>::type;

        // TODO: no value
        kstd::OptionalValue<ValueType> result;

        auto volumeOpt = inner_get<ClassThisType>(a_this, a_key_volume);
        if (volumeOpt)
        {
            auto& volume = *volumeOpt.getPtr();

            auto it_node = volume.find(a_key_node);
            if (volume.end() != it_node)
            {
                result.set(it_node->second);
            }
            else
            {
                LOG_ERROR("No such callback node (", "volume:", a_key_volume,
                          "node:", a_key_node, ")");
            }
        }

        return result;
    }
};
} // namespace kstd

//--------------------------------------------------------------------------------
