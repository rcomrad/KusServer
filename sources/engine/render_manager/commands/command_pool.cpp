#include "command_pool.hpp"

#include <iostream>

#include "engine/render_manager/device/device.hpp"

namespace kusengine::render
{

CommandPool&
CommandPool::getInstance()
{
    static CommandPool command_pool;
    return command_pool;
}

void
CommandPool::create()
{
    auto queue_family_indices = DEVICE_INSTANCE.getQueueFamilyIndices();

    vk::CommandPoolCreateInfo poolInfo;
    poolInfo.flags = vk::CommandPoolCreateFlags() |
                     vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
    poolInfo.queueFamilyIndex = queue_family_indices.graphics_family.value();

    m_command_pool = LOGICAL_DEVICE_INSTANCE.createCommandPoolUnique(poolInfo);
}

vk::UniqueCommandBuffer
CommandPool::allocateCommandBuffer() const
{
    vk::CommandBufferAllocateInfo alloc_info = {};
    alloc_info.commandPool                   = m_command_pool.get();
    alloc_info.level                         = vk::CommandBufferLevel::ePrimary;
    alloc_info.commandBufferCount            = 1;

    return std::move(
        LOGICAL_DEVICE_INSTANCE.allocateCommandBuffersUnique(alloc_info)[0]);
}
} // namespace kusengine::render
