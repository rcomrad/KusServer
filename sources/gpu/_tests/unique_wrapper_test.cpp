#include "kernel/tester/fixture.hpp"
#include "kernel/utility/macroses/holy_trinity.hpp"

#include <cstdint>
#include <utility>

#include "gpu/utils/vulkan_move_monitor.hpp"

namespace kustest
{

namespace
{

struct FakeHandle
{
    uint64_t value = 0;

    FakeHandle() = default;
    explicit FakeHandle(uint64_t a_value) : value(a_value)
    {
    }

    explicit operator bool() const
    {
        return value != 0;
    }
};

struct FakeContext
{
    int* destroyed;
};

struct FakeDeleter
{
    static void operator()(FakeContext& a_context, FakeHandle& a_handle) noexcept
    {
        ++*a_context.destroyed;
        a_handle.value = 0;
    }
};

using FakeWrapper =
    gpu::VulkanUniqueWrapper<FakeHandle, FakeDeleter, FakeContext>;

} // namespace

TEST(UniqueWrapperTest, MoveConstructionTransfersHandleAndDeletesOnce)
{
    int destroyed  = 0;
    FakeContext ctx{&destroyed};

    {
        FakeWrapper source(FakeHandle(42), ctx);
        FakeWrapper target(std::move(source));

        EXPECT_EQ(target.toBase().value, 42u);
        EXPECT_EQ(source.toBase().value, 0u);
    }

    EXPECT_EQ(destroyed, 1);
}

TEST(UniqueWrapperTest, MoveAssignmentTransfersHandleAndDeletesOnce)
{
    int destroyed  = 0;
    FakeContext ctx{&destroyed};

    {
        FakeWrapper source(FakeHandle(1), ctx);
        FakeWrapper target(FakeHandle(2), ctx);

        target = std::move(source);

        EXPECT_EQ(target.toBase().value, 1u);
        EXPECT_EQ(source.toBase().value, 0u);
    }

    EXPECT_EQ(destroyed, 1);
}

TEST(UniqueWrapperTest, SelfMoveAssignmentKeepsHandle)
{
    int destroyed  = 0;
    FakeContext ctx{&destroyed};

    {
        FakeWrapper wrapper(FakeHandle(7), ctx);
        wrapper = std::move(wrapper);

        EXPECT_EQ(wrapper.toBase().value, 7u);
    }

    EXPECT_EQ(destroyed, 1);
}

} // namespace kustest
