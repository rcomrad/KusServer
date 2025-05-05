#include "renderer.hpp"

#include <iostream>

#include "engine/window/window.hpp"

namespace kusengine
{

Renderer::Renderer() : m_swap_chain(m_render_pass)
{
}

vk::Extent2D
Renderer::swapchainExtent() const
{
    return m_swap_chain.extent();
}

bool
Renderer::createPipelineLayout()
{
    vk::PipelineLayoutCreateInfo layoutInfo;
    layoutInfo.flags          = vk::PipelineLayoutCreateFlags();
    layoutInfo.setLayoutCount = 1;
    layoutInfo.pSetLayouts =
        &(m_descriptor_manager.descriptorSetLayout().descriptorSetLayout());
    layoutInfo.pushConstantRangeCount = 0;
    try
    {
        m_pipeline_layout =
            LOGICAL_DEVICE.createPipelineLayoutUnique(layoutInfo);
    }
    catch (vk::SystemError err)
    {
        std::cerr << err.what() << '\n';
        return false;
    }
    return true;
}

bool
Renderer::initRenderer(Window& window)
{
    if (!m_instance.create("KusRendering")) return false;

    if (!m_swap_chain.createSurface(window, m_instance)) return false;

    if (!DEVICE.create(m_instance, m_swap_chain.surface())) return false;

    if (!m_swap_chain.create(window.getExtent().width,
                             window.getExtent().height))
        return false;

    m_descriptor_manager.create();

    if (!createPipelineLayout()) return false;

    if (!m_render_pass.create(m_pipeline_layout.get(), m_swap_chain.format(),
                              m_swap_chain.extent()))
        return false;

    if (!COMMAND_POOL.create()) return false;

    frame_number = 0;
    max_frames_in_flight =
        m_swap_chain.createSwapChainFrames(m_descriptor_manager);

    return true;
}

void
Renderer::drawFrameImpl(Window& window, const Scene& scene)
{
    m_swap_chain.drawFrame(frame_number, scene, m_pipeline_layout.get());

    frame_number = (frame_number + 1) % max_frames_in_flight;
}

}; // namespace kusengine
