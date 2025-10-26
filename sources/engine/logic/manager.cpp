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
    m_device.create(storage.get<vk::PhysicalDevice>(),
                    storage.get<type::FamilyIndex>());
    storage.put(m_device->get());
}

void
Manager::createCommandEnv()
{
    SCOPED_TRACE_INIT("command environment");

    auto& storage = *m_obj_ref_storage;
    m_command_pool.create(storage.get<vk::Device>(),
                          storage.get<type::FamilyIndex>());
    m_queue.create(storage.get<vk::Device>(), storage.get<type::FamilyIndex>(),
                   0);
    m_command_buffers =
        m_command_pool->alocateBuffers(storage.get<vk::Device>(), 3);
}

void
Manager::nextTick()
{
    auto& swap_chain = m_obj_ref_storage->get<vk::SwapchainKHR>();
    auto& device     = m_obj_ref_storage->get<vk::Device>();

    auto index = m_queue->acquire_next_image(device, swap_chain);
    LOG_DEBUG("Next index is: %d", index);
    m_queue->submit(*m_command_buffers.at(index));
    m_queue->present(index, swap_chain);
}

std::vector<vk::UniqueCommandBuffer>&
Manager::getCommandBuffers()
{
    return m_command_buffers;
}

} // namespace engine::logic
