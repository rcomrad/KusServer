#include "command_pool.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

CommandPool::CommandPool(logic::Device a_device,
                         type::FamilyIndex a_family_index)
    : vk::CommandPool(create(a_device, a_family_index)), m_device(a_device)
{
}

CommandPool::~CommandPool()
{
    m_device.destroyCommandPool(*static_cast<vk::CommandPool*>(this));
}

vk::CommandPool
CommandPool::create(logic::Device a_device, type::FamilyIndex a_family_index)
{
    SCOPED_TRACE_INIT("command pool");

    vk::CommandPoolCreateInfo info;
    info.setQueueFamilyIndex(a_family_index)
        .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
    return a_device.createCommandPool(info);
}

std::vector<vk::UniqueCommandBuffer>
CommandPool::alocateBuffers(uint32_t a_size)
{
    vk::CommandBufferAllocateInfo allocate_info;
    allocate_info.setLevel(vk::CommandBufferLevel::ePrimary)
        .setCommandBufferCount(a_size)
        .setCommandPool(*this)
        .setLevel(vk::CommandBufferLevel::ePrimary);

    return m_device.allocateCommandBuffersUnique(allocate_info);
}

} // namespace engine::logic
