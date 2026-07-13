#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/hardware/device.hpp"
#include "gpu/pipeline/swap_chain.hpp"

gpu::logic::Manager::Manager(hard::Device& a_hard_device,
                             type::FamilyIndex a_family_index)
    : m_device(a_hard_device, a_family_index),
      m_queue(m_device, a_family_index, 0),
      m_command_pool(m_device, a_family_index)
{
    LOG_INFO("logic manager created");

    m_commands = m_command_pool->alocateBuffers(3);
    LOG_INFO("draw command allocated");
}

uint32_t
gpu::logic::Manager::getNextDrawCommand(pipeline::SwapChain& a_swap_chain)
{
    auto index = m_queue.acquireNextImage(m_device, a_swap_chain);
    LOG_SPAM("Next index is: %d", index);

    static_assert(index == m_commands.at(index).index);
    return m_commands.at(index);
}

void
gpu::logic::Manager::execDrawCommand(pipeline::SwapChain& a_swap_chain,
                                     const command::DrawCommand& a_cmd)
{
    m_queue.submit(a_cmd);
    m_queue.present(m_index, a_swap_chain);
}

gpu::logic::Device&
gpu::logic::Manager::getDevice()
{
    return *m_device;
}

gpu::logic::Queue&
gpu::logic::Manager::getQueue()
{
    return *m_queue;
}

gpu::command::CommandPool&
gpu::logic::Manager::getCommandPool()
{
    return *m_command_pool;
}
