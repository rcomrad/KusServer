#include "kernel/tester/fixture.hpp"

#include "gpu/utils/typedef.hpp"

namespace kustest
{

TEST(SomeIndexTest, DefaultValueIsZero)
{
    gpu::type::SomeIndex<int> value;
    EXPECT_EQ(value.value, 0);
}

TEST(SomeIndexTest, StoresAssignsAndConvertsUnderlyingValue)
{
    gpu::type::SomeIndex<int> value(7);

    EXPECT_EQ(value, 7);
    EXPECT_EQ(static_cast<int>(value), 7);

    value = 11;
    EXPECT_EQ(value.value, 11);
}

TEST(SomeIndexTest, PreIncrementUpdatesValue)
{
    gpu::type::SomeIndex<int> value(4);

    auto& result = ++value;

    EXPECT_EQ(value.value, 5);
    EXPECT_EQ(result.value, 5);
}

TEST(SomeIndexTest, PostIncrementUpdatesValue)
{
    gpu::type::SomeIndex<int> value(4);

    // The current implementation increments immediately and returns a
    // reference, so this test documents the existing semantics.
    auto& result = value++;

    EXPECT_EQ(value.value, 5);
    EXPECT_EQ(result.value, 5);
}

TEST(MemoryTypeBitsTest, AndAssignmentKeepsIntersection)
{
    gpu::type::MemoryTypeBits lhs(0b1100);
    gpu::type::MemoryTypeBits rhs(0b1010);

    lhs &= rhs;

    EXPECT_EQ(lhs.value, 0b1000);
}

} // namespace kustest
