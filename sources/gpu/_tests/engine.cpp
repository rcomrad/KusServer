#include "vulkan_fixture.hpp"

namespace kustest
{

class EngineTest : public VulkanFixture
{
};

TEST_F(EngineTest, smoke)
{
    EXPECT_FALSE(instance().getPhysicalDevices().empty());
    EXPECT_FALSE(physicalDevice().getName().empty());
}

} // namespace kustest
