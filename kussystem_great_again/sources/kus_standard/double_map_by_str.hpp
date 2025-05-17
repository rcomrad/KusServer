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
    using InnerValure = std::unordered_map<std::string_view, ValueType>;
    using UpperValue  = std::unordered_map<std::string_view, InnerValure>;

    class MapNode
    {
    public:
        HOLY_TRINITY_NO_RELEASE_COPY(MapNode);

        ValueType& operator[](const char* a_key) noexcept
        {
            std::string_view key_view(a_key);
            auto key_it = m_cur_cell.find(key_view);
            if (key_it == m_cur_cell.end())
            {
                key_view = m_this->m_key_buffer.add(a_key);
                key_it   = m_cur_cell.emplace(key_view, ValueType()).first;
            }
            return key_it->second;
        }

        MapNode(DoubleMapByStr* a_ptr, InnerValure& a_iter)
            : m_this(a_ptr), m_cur_cell(a_iter)
        {
        }

    private:
        DoubleMapByStr* m_this;
        InnerValure& m_cur_cell;
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
            InnerValure temp; // TODO: remove
            key_it = m_map.emplace(key_view, std::move(temp)).first;
        }

        return MapNode(this, key_it->second);
    }

    auto get(const char* a_key_volume) noexcept
    {
        return innerGet<DoubleMapByStr*>(this, a_key_volume);
    }

    auto get(const char* a_key_volume) const noexcept
    {
        return innerGet<const DoubleMapByStr*>(this, a_key_volume);
    }

    auto get(const char* a_key_volume, const char* a_key_node) noexcept
    {
        return innerGet<DoubleMapByStr*>(this, a_key_volume, a_key_node);
    }

    auto get(const char* a_key_volume, const char* a_key_node) const noexcept
    {
        return innerGet<const DoubleMapByStr*>(this, a_key_volume, a_key_node);
    }

private:
    CharBuffer<Name, Size> m_key_buffer;
    UpperValue m_map;

    template <typename ClassThisType>
    static auto innerGet(ClassThisType a_this,
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
        kstd::OptionalPtr<InnerValure> result;

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
    static auto innerGet(ClassThisType a_this,
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

        auto volumeOpt = innerGet<ClassThisType>(a_this, a_key_volume);
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
