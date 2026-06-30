#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

#include "engine/graphics/swap_chain.hpp"

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
    // m_buffer.create(*m_device, 65000);
    storage.put(*m_device);
}

std::vector<logic::BaseCommand>
Manager::createCommandEnv()
{
    SCOPED_TRACE_INIT("command environment");

    auto& storage = *m_obj_ref_storage;
    m_command_pool.create(storage.get<logic::Device>(),
                          storage.get<type::FamilyIndex>());
    m_queue.create(storage.get<logic::Device>(),
                   storage.get<type::FamilyIndex>(), 0);
    return m_command_pool->alocateBuffers(3);
}

uint32_t
Manager::startNextTick()
{
    auto& swap_chain = m_obj_ref_storage->get<graphics::SwapChain>();
    auto& device     = m_obj_ref_storage->get<logic::Device>();
    m_index          = m_queue->acquire_next_image(device, swap_chain);
    LOG_DEBUG("Next index is: %d", m_index);
    return m_index;
}

void
Manager::commitNextTick(const logic::BaseCommand& a_cmd)
{
    auto& swap_chain = m_obj_ref_storage->get<graphics::SwapChain>();
    auto& device     = m_obj_ref_storage->get<logic::Device>();

    LOG_DEBUG("Using index: %d", m_index);
    m_queue->submit(a_cmd);
    m_queue->present(m_index, swap_chain);
}

void
Manager::collapseImagesBuffer(ImagesBuffer& a_images_buffer,
                              vk::DescriptorSetLayout a_desc_set_layout)
{
    a_images_buffer.collapse(*m_command_pool, *m_queue, a_desc_set_layout);
}

// std::vector<logic::BaseCommand>&
// Manager::getCommandBuffers()
// {
//     return m_command_buffers;
// }

} // namespace engine::logic
