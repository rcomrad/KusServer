#include "kernel/tester/fixture.hpp"

#include "gpu/utils/typedef.hpp"

namespace kustest
{

TEST(PairGeometryTest, AddsCoordinates)
{
    gpu::type::Coordinates lhs(10, 20);
    gpu::type::Coordinates rhs(5, -3);

    auto result = lhs + rhs;

    EXPECT_EQ(result.x, 15);
    EXPECT_EQ(result.y, 17);
}

TEST(PairGeometryTest, SubtractsCoordinates)
{
    gpu::type::Coordinates lhs(10, 20);
    gpu::type::Coordinates rhs(4, 6);

    auto result = lhs - rhs;

    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 14);
}

TEST(PairGeometryTest, DivisionReturnsFloatingPointPair)
{
    gpu::type::CoordinateSize size(100, 50);
    gpu::type::CoordinateSize divisor(2, 4);

    auto result = size / divisor;

    EXPECT_FLOAT_EQ(result.x, 50.0f);
    EXPECT_FLOAT_EQ(result.y, 12.5f);
}

TEST(PairGeometryTest, CreatesVulkanExtent)
{
    gpu::type::CoordinateSize size(640, 480);

    auto extent = gpu::type::createExtend3D(size);

    EXPECT_EQ(extent.width, 640u);
    EXPECT_EQ(extent.height, 480u);
    EXPECT_EQ(extent.depth, 1u);
}

TEST(PairGeometryTest, InsideRequiresBothComponentsToBeGreater)
{
    gpu::type::Coordinates outer(100, 100);
    gpu::type::Coordinates inner(10, 20);
    gpu::type::Coordinates boundary(10, 100);

    EXPECT_TRUE(outer.inside(inner));
    EXPECT_FALSE(inner.inside(outer));
    EXPECT_FALSE(boundary.inside(outer));
}

} // namespace kustest
