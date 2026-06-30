#include "command_pool.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

CommandPool::CommandPool(logic::Device& a_device,
                         type::FamilyIndex a_family_index)
    : vk::CommandPool(create(a_device, a_family_index)), m_device(a_device)
{
}

CommandPool::~CommandPool()
{
    m_device.destroyCommandPool(toBase());
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

logic::BaseCommand
CommandPool::alocateBuffer()
{
    return BaseCommand(m_device, *this, alocate(1)[0]);
}

std::vector<logic::BaseCommand>
CommandPool::alocateBuffers(uint32_t a_size)
{
    std::vector<logic::BaseCommand> result;
    for (auto& i : alocate(a_size))
    {
        result.emplace_back(m_device, *this, i);
    }
    return result;
}

logic::OneTimeCommand
CommandPool::alocateOneTimeCommand()
{
    return OneTimeCommand(m_device, *this, alocate(1)[0]);
}

std::vector<vk::CommandBuffer>
CommandPool::alocate(uint32_t a_size)
{
    vk::CommandBufferAllocateInfo allocate_info;
    allocate_info.setLevel(vk::CommandBufferLevel::ePrimary)
        .setCommandBufferCount(a_size)
        .setCommandPool(toBase())
        .setLevel(vk::CommandBufferLevel::ePrimary);
    auto tt = m_device.allocateCommandBuffers(allocate_info);
    return tt;
}

} // namespace engine::logic
