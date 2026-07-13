#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/command/draw_command.hpp"
#include "gpu/logic/device.hpp"
#include "gpu/window/surface.hpp"
#include "gpu/window/surface_characteristics.hpp"

gpu::pipeline::Manager::Manager(
    logic::Device a_device,
    window::Surface& a_surface,
    const window::SurfaceCharacteristics& a_characteristic)
    : m_swap_chain(a_device, a_surface, a_characteristic),
      m_render_pass(a_device, a_characteristic.format),
      m_image_collection.create(a_device,
                                m_swap_chain,
                                m_render_pass,
                                a_characteristic.format),
      m_shaiders({a_device, "vert.spv"}, {a_device, "frag.spv"}),
      m_graphics_pipeline.create(a_device,
                                 m_render_pass,
                                 m_shaiders.at(0),
                                 m_shaiders.at(1));
{
    LOG_INFO("graphics manager created");
}

void
gpu::pipeline::Manager::bindToNextImage(command::DrawCommand& a_cmd_buff)
{
    LOG_SPAM("bindToNextImage");

    a_cmd_buff.beginRenderPass(
        m_render_pass->getBeginInfo(
            m_image_collection->getFrame(a_cmd_buff.index)),
        vk::SubpassContents::eInline);
    a_cmd_buff.bindPipeline(vk::PipelineBindPoint::eGraphics,
                            m_graphics_pipeline->get());
}

gpu::pipeline::SwapChain&
gpu::pipeline::Manager::getSwapChain()
{
    return m_swap_chain;
}
