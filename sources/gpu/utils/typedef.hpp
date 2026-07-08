#pragma once

#include "kernel/utility/type/declaration/pair.hpp"
#include <vulkan/vulkan.hpp>

#include <cstdint>

namespace gpu::type
{

template <typename T, typename... Args>
struct SomeIndex
{
    T value;

    operator T() const
    {
        return value;
    }

    SomeIndex() : value{}
    {
    }
    SomeIndex(T a_value) : value(a_value)
    {
    }

    SomeIndex& operator=(T a_value)
    {
        value = a_value;
        return *this;
    }

    SomeIndex& operator++()
    {
        value += 1;
        return *this;
    }

    SomeIndex& operator++(int)
    {
        value += 1;
        return *this;
    }
};

using FamilyIndex     = SomeIndex<uint32_t, void>;
using ImageNum        = SomeIndex<uint32_t, void, void>;
using MemoryTypeIndex = SomeIndex<uint32_t, void, void, void, void>;
using MemoryTypeBits  = SomeIndex<uint32_t, void, void, void, void, void>;
using QueueIndex      = SomeIndex<int, void>;
using AnimationFrame =
    SomeIndex<int, void, void>; // TODO: not default constructed?

inline MemoryTypeBits&
operator&=(MemoryTypeBits& lhs, MemoryTypeBits rhs)
{
    lhs.value &= rhs.value;
    return lhs;
}

using Dimensions     = core::Pair<int>;
using Coordinates    = core::Pair<int>;
using CoordinateSize = core::Pair<int>;
using NDC            = core::Pair<float>;

template <typename T>
vk::Extent3D
createExtend3D(const core::Pair<T>& a_coord)
{
    return vk::Extent3D(static_cast<uint32_t>(a_coord.width),
                        static_cast<uint32_t>(a_coord.height), 1);
}

} // namespace gpu::type
