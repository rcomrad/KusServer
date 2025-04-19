#include "renderer.hpp"

#include <iostream>

#include "engine/window/window.hpp"

namespace kusengine
{

Renderer::Renderer()
    : m_command_pool(m_device),
      m_swap_chain(m_command_pool, m_device, m_render_pass),
      m_triangle_mesh(m_device)
{
}

bool
Renderer::createPipelineLayout()
{
    vk::PipelineLayoutCreateInfo layoutInfo;
    layoutInfo.flags                  = vk::PipelineLayoutCreateFlags();
    layoutInfo.setLayoutCount         = 0;
    layoutInfo.pushConstantRangeCount = 0;
    try
    {
        m_pipeline_layout =
            m_device.logicalDeviceConstRef().createPipelineLayoutUnique(
                layoutInfo);
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

    if (!m_device.create(m_instance, m_swap_chain.surface())) return false;

    if (!m_swap_chain.create(window.getExtent().width,
                             window.getExtent().height))
        return false;

    if (!createPipelineLayout()) return false;

    if (!m_render_pass.create(m_device.logicalDeviceConstRef(),
                              m_pipeline_layout.get(), m_swap_chain.format(),
                              m_swap_chain.extent()))
        return false;

    if (!m_command_pool.create()) return false;

    m_swap_chain.createSwapChainFrames();

    // if (!m_sync_control.create()) return false;

    frame_number         = 0;
    max_frames_in_flight = 2;

    return true;
}

void
Renderer::deviceWaitIdle()
{
}

void
Renderer::drawFrameImpl(Window& window)
{
    m_swap_chain.drawFrame(frame_number, m_triangle_mesh);

    frame_number = (frame_number + 1) % max_frames_in_flight;
}

// void
// Renderer::drawFrameImpl(const Window& window)
// {
//     vkDeviceWaitIdle(m_device.logicalDeviceConstRef());
//     m_swap_chain.recreate(window, m_instance);
//     drawFrameImpl();
// }

}; // namespace kusengine
