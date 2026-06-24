#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine::graphics
{

Manager::Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_obj_ref_storage(a_obj_ref_storage)
{
    Shader::init();
}

void
Manager::reset()
{
    SCOPED_TRACE_INIT("graphics manager");

    auto& storage = *m_obj_ref_storage;

    auto& device = storage.get<logic::Device>();
    device.waitIdle();

    m_swap_chain.create(
        device, storage.get<vk::SurfaceKHR>(), storage.get<type::FamilyIndex>(),
        storage.get<vk::Format>(), storage.get<vk::ColorSpaceKHR>(),
        storage.get<vk::PresentModeKHR>(),
        storage.get<vk::SurfaceCapabilitiesKHR>(),
        storage.get<type::ImageNum>());

    m_render_pass.create(device, storage.get<vk::Format>());
    m_image_collection.create(device, **m_swap_chain, **m_render_pass,
                              storage.get<vk::Format>());
    createShaider("vert.spv");
    createShaider("frag.spv");
    m_graphics_pipeline.create(device, **m_render_pass, *m_shaiders.at(0),
                               *m_shaiders.at(1));

    storage.reset(*m_swap_chain);
    storage.reset(*m_render_pass);
    storage.reset(m_graphics_pipeline->get());
}

void
Manager::bindToNextImage(int a_image_num, logic::BaseCommand& a_cmd_buff)
{
    SCOPED_TRACE_FUNC("bindToNextImage");

    a_cmd_buff.beginRenderPass(
        m_render_pass->getBeginInfo(m_image_collection->getFrame(a_image_num)),
        vk::SubpassContents::eInline);
    a_cmd_buff.bindPipeline(vk::PipelineBindPoint::eGraphics,
                            m_graphics_pipeline->get());
}

void
Manager::createShaider(std::string_view a_name)
{
    m_shaiders.emplace_back(
        Shader::create(m_obj_ref_storage->get<logic::Device>(), a_name));
}

} // namespace engine::graphics
