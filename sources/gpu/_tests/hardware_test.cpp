#include "vulkan_fixture.hpp"

#include <vulkan/vulkan.hpp>

namespace kustest
{

class HardwareTest : public VulkanFixture
{
};

TEST_F(HardwareTest, InstanceEnumeratesPhysicalDevices)
{
    auto devices = instance().getPhysicalDevices();
    EXPECT_FALSE(devices.empty());
}

TEST_F(HardwareTest, PhysicalDeviceHasName)
{
    EXPECT_FALSE(physicalDevice().getName().empty());
}

TEST_F(HardwareTest, PhysicalDeviceReportsQueueFamilies)
{
    auto families = physicalDevice().getQueueFamilyProperties();
    EXPECT_FALSE(families.empty());
    EXPECT_LT(familyIndex().value, families.size());
}

TEST_F(HardwareTest, FindsDeviceLocalMemoryForBuffer)
{
    vk::BufferCreateInfo info;
    info.setSize(1024).setUsage(vk::BufferUsageFlagBits::eTransferSrc);
    auto buffer = device().createBufferUnique(info);

    auto requirements = device().getBufferMemoryRequirements(*buffer);
    auto index        = physicalDevice().getMemoryTypeIndex(
        requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);

    auto properties = physicalDevice().getMemoryProperties();
    EXPECT_LT(index.value, properties.memoryTypeCount);
    EXPECT_TRUE(static_cast<bool>(
        properties.memoryTypes[index.value].propertyFlags &
        vk::MemoryPropertyFlagBits::eDeviceLocal));
}

TEST_F(HardwareTest, LogicDeviceDelegatesMemoryTypeSelection)
{
    vk::BufferCreateInfo info;
    info.setSize(256).setUsage(vk::BufferUsageFlagBits::eTransferSrc);
    auto buffer = device().createBufferUnique(info);

    auto requirements = device().getBufferMemoryRequirements(*buffer);
    auto index        = device().getMemoryTypeIndex(
        requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible);

    auto properties = physicalDevice().getMemoryProperties();
    EXPECT_LT(index.value, properties.memoryTypeCount);
    EXPECT_TRUE(static_cast<bool>(
        properties.memoryTypes[index.value].propertyFlags &
        vk::MemoryPropertyFlagBits::eHostVisible));
}

} // namespace kustest
