#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/pipeline/swap_chain.hpp"

gpu::logic::Manager::Manager(
    std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_obj_ref_storage(a_obj_ref_storage)
{
}

void
gpu::logic::Manager::initialize()
{
    SCOPED_TRACE_INIT("logic manager");

    auto& storage = *m_obj_ref_storage;
    m_device.create(storage.get<hard::Device>(),
                    storage.get<type::FamilyIndex>());
    storage.put(*m_device);
}

std::vector<gpu::command::BaseCommand>
gpu::logic::Manager::createCommandEnv()
{
    SCOPED_TRACE_INIT("command environment");

    auto& storage = *m_obj_ref_storage;
    m_queue.create(storage.get<logic::Device>(),
                   storage.get<type::FamilyIndex>(), 0);
    m_command_pool.create(storage.get<logic::Device>(),
                          storage.get<type::FamilyIndex>());
    return m_command_pool->alocateBuffers(3);
}

uint32_t
gpu::logic::Manager::startNextTick()
{
    auto& swap_chain = m_obj_ref_storage->get<pipeline::SwapChain>();
    auto& device     = m_obj_ref_storage->get<logic::Device>();
    m_index          = m_queue->acquireNextImage(device, swap_chain);
    LOG_SPAM("Next index is: %d", m_index);
    return m_index;
}

void
gpu::logic::Manager::commitNextTick(const command::BaseCommand& a_cmd)
{
    auto& swap_chain = m_obj_ref_storage->get<pipeline::SwapChain>();
    auto& device     = m_obj_ref_storage->get<logic::Device>();

    LOG_SPAM("Using index: %d", m_index);
    m_queue->submit(a_cmd);
    m_queue->present(m_index, swap_chain);
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
