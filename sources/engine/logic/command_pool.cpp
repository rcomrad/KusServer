#include "command_pool.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

CommandPool::CommandPool(vk::Device a_device, type::FamilyIndex a_family_index)
{
    SCOPED_TRACE_INIT("command pool");

    vk::CommandPoolCreateInfo info;
    info.setQueueFamilyIndex(a_family_index);
    m_command_pool = a_device.createCommandPoolUnique(info);
}

std::vector<vk::UniqueCommandBuffer>
CommandPool::alocateBuffers(vk::Device a_device, uint32_t a_size)
{
    vk::CommandBufferAllocateInfo allocate_info;
    allocate_info.setLevel(vk::CommandBufferLevel::ePrimary)
        .setCommandBufferCount(a_size)
        .setCommandPool(*m_command_pool)
        .setLevel(vk::CommandBufferLevel::ePrimary);

    return a_device.allocateCommandBuffersUnique(allocate_info);
}

} // namespace engine::logic
