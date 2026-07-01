#pragma once

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
using QueueIndex      = SomeIndex<int, void, void, void>;

inline MemoryTypeBits&
operator&=(MemoryTypeBits& lhs, MemoryTypeBits rhs)
{
    lhs.value &= rhs.value;
    return lhs;
}

} // namespace gpu::type
