#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine::logic
{

Manager::Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_obj_ref_storage(a_obj_ref_storage)
{
}

void
Manager::initialize()
{
    SCOPED_TRACE_INIT("logic manager");

    auto& storage = *m_obj_ref_storage;
    m_device.create(storage.get<hard::Device>(),
                    storage.get<type::FamilyIndex>());
    storage.put(*m_device);
}

void
Manager::createCommandEnv()
{
    SCOPED_TRACE_INIT("command environment");

    auto& storage = *m_obj_ref_storage;
    m_command_pool.create(storage.get<logic::Device>(),
                          storage.get<type::FamilyIndex>());
    m_queue.create(storage.get<logic::Device>(),
                   storage.get<type::FamilyIndex>(), 0);
    m_command_buffers = m_command_pool->alocateBuffers(3);
}

void
Manager::nextTick(
    std::function<void(int, vk::UniqueCommandBuffer&)> a_record_callback)
{
    auto& swap_chain = m_obj_ref_storage->get<vk::SwapchainKHR>();
    auto& device     = m_obj_ref_storage->get<logic::Device>();

    auto index = m_queue->acquire_next_image(device, swap_chain);
    LOG_DEBUG("Next index is: %d", index);
    auto& cmd = m_command_buffers.at(index);
    a_record_callback(index, cmd);
    m_queue->submit(*cmd);
    m_queue->present(index, swap_chain);
}

std::vector<vk::UniqueCommandBuffer>&
Manager::getCommandBuffers()
{
    return m_command_buffers;
}

} // namespace engine::logic
