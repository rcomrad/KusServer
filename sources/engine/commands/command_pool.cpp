#include "command_pool.hpp"

#include <iostream>

#include "engine/device/device.hpp"

namespace kusengine
{

CommandPool::CommandPool(const Device& device) : device_ref(device)
{
}

bool
CommandPool::create()
{
    auto queue_family_indices = device_ref.getQueueFamilyIndices();

    vk::CommandPoolCreateInfo poolInfo;
    poolInfo.flags = vk::CommandPoolCreateFlags() |
                     vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
    poolInfo.queueFamilyIndex = queue_family_indices.graphics_family.value();

    try
    {
        m_command_pool =
            device_ref.logicalDeviceConstRef().createCommandPoolUnique(
                poolInfo);
    }
    catch (vk::SystemError err)
    {
        std::cerr << err.what() << '\n';
        return false;
    }
    return true;
}

vk::UniqueCommandBuffer
CommandPool::allocateCommandBuffer() const
{
    vk::CommandBufferAllocateInfo alloc_info = {};
    alloc_info.commandPool                   = m_command_pool.get();
    alloc_info.level                         = vk::CommandBufferLevel::ePrimary;
    alloc_info.commandBufferCount            = 1;

    return std::move(
        device_ref.logicalDeviceConstRef().allocateCommandBuffersUnique(
            alloc_info)[0]);
}

} // namespace kusengine
