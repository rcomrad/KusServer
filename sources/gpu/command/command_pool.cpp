#include "command_pool.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "gpu/logic/device.hpp"

#include "gpu/logic/device.hpp"

gpu::command::CommandPool::CommandPool(logic::Device& a_device,
                                       type::FamilyIndex a_family_index)
    : vk::CommandPool(create(a_device, a_family_index)), m_device(a_device)
{
}

gpu::command::CommandPool::~CommandPool()
{
    m_device.destroyCommandPool(toBase());
}

vk::CommandPool
gpu::command::CommandPool::create(logic::Device& a_device,
                                  type::FamilyIndex a_family_index)
{
    SCOPED_TRACE_INIT("command pool");

    vk::CommandPoolCreateInfo info;
    info.setQueueFamilyIndex(a_family_index)
        .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
    return a_device.createCommandPool(info);
}

gpu::command::BaseCommand
gpu::command::CommandPool::alocateBuffer()
{
    return BaseCommand(m_device, *this, alocate(1)[0]);
}

std::vector<gpu::command::BaseCommand>
gpu::command::CommandPool::alocateBuffers(uint32_t a_size)
{
    std::vector<BaseCommand> result;
    for (auto& i : alocate(a_size))
    {
        result.emplace_back(m_device, *this, i);
    }
    return result;
}

gpu::command::OneTimeCommand
gpu::command::CommandPool::alocateOneTimeCommand()
{
    return OneTimeCommand(m_device, *this, alocate(1)[0]);
}

std::vector<vk::CommandBuffer>
gpu::command::CommandPool::alocate(uint32_t a_size)
{
    vk::CommandBufferAllocateInfo allocate_info;
    allocate_info.setLevel(vk::CommandBufferLevel::ePrimary)
        .setCommandBufferCount(a_size)
        .setCommandPool(toBase())
        .setLevel(vk::CommandBufferLevel::ePrimary);
    auto tt = m_device.allocateCommandBuffers(allocate_info);
    return tt;
}
