#include "command_pool.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "gpu/logic/device.hpp"

gpu::command::CommandPool::CommandPool(logic::Device& a_device,
                                       type::FamilyIndex a_family_index)
    : CommandPoolBase(create(a_device, a_family_index), a_device)
{
}

void
gpu::command::CommandPoolDeleter::operator()(logic::Device& a_device,
                                             vk::CommandPool& a_this) noexcept
{
    a_device.destroyCommandPool(a_this);
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
    return BaseCommand(getContext(), *this, alocate(1)[0]);
}

std::vector<gpu::command::DrawCommand>
gpu::command::CommandPool::alocateDrawBuffers(uint32_t a_size)
{
    int index = 0;
    std::vector<DrawCommand> result;
    for (auto& i : alocate(a_size))
    {
        result.emplace_back(getContext(), *this, i, index++);
    }
    return result;
}

gpu::command::OneTimeCommand
gpu::command::CommandPool::alocateOneTimeCommand()
{
    return OneTimeCommand(getContext(), *this, alocate(1)[0]);
}

std::vector<vk::CommandBuffer>
gpu::command::CommandPool::alocate(uint32_t a_size)
{
    vk::CommandBufferAllocateInfo allocate_info;
    allocate_info.setLevel(vk::CommandBufferLevel::ePrimary)
        .setCommandBufferCount(a_size)
        .setCommandPool(toBase())
        .setLevel(vk::CommandBufferLevel::ePrimary);
    auto tt = getContext().allocateCommandBuffers(allocate_info);
    return tt;
}
