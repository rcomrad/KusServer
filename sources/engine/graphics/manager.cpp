#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine::graphics
{

Manager::Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_next_image(0), m_obj_ref_storage(a_obj_ref_storage)
{
}

void
Manager::initialize()
{

    SCOPED_TRACE_INIT("graphics manager");
    auto& storage = *m_obj_ref_storage;

    m_swap_chain.create(
        storage.get<vk::Device>(), storage.get<vk::SurfaceKHR>(),
        storage.get<type::FamilyIndex>(), storage.get<vk::Format>(),
        storage.get<vk::ColorSpaceKHR>(), storage.get<vk::PresentModeKHR>(),
        storage.get<vk::SurfaceCapabilitiesKHR>(),
        storage.get<type::ImageNum>());
    m_render_pass.create(storage.get<vk::Device>(), storage.get<vk::Format>());

    Shader::init();
    m_image_collection.create(storage.get<vk::Device>(), m_swap_chain->get(),
                              m_render_pass->get(), storage.get<vk::Format>());
    createShaider("vert.spv");
    createShaider("frag.spv");
    m_graphics_pipeline.create(storage.get<vk::Device>(), m_render_pass->get(),
                               *m_shaiders.at(0), *m_shaiders.at(1));

    storage.put(m_swap_chain->get());
    storage.put(m_render_pass->get());
    storage.put(m_graphics_pipeline->get());
}

void
Manager::bindToNextImage(vk::CommandBuffer a_cmd_buff)
{
    SCOPED_TRACE_FUNC("bindToNextImage");

    a_cmd_buff.beginRenderPass(
        m_render_pass->getBeginInfo(
            m_image_collection->getFrame(m_next_image++)),
        vk::SubpassContents::eInline);
    a_cmd_buff.bindPipeline(vk::PipelineBindPoint::eGraphics,
                            m_graphics_pipeline->get());
}

void
Manager::createShaider(std::string_view a_name)
{
    m_shaiders.emplace_back(
        Shader::create(m_obj_ref_storage->get<vk::Device>(), a_name));
}

} // namespace engine::graphics
