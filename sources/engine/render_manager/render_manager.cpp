#include "render_manager.hpp"

#include "engine/render_manager/device/device.hpp"
#include "engine/window/window.hpp"

namespace kusengine
{
namespace render
{
RenderManager::RenderManager()
{
}

RenderManager&
RenderManager::getInstance()
{
    static RenderManager r_manager;
    return r_manager;
}
// --- init / shutdown --- //
void
RenderManager::init(const kusengine::Window& window)
{
    auto window_extent = window.getExtent();

    m_instance.create("KusEngine");

    m_swap_chain.createSurface(window, m_instance);

    DEVICE_INSTANCE.create(m_instance, m_swap_chain.surface());

    m_swap_chain.create(window_extent.width, window_extent.height);

    m_render_way_storage.create(m_swap_chain.extent(), m_swap_chain.format());

    frame_number = 0;

    max_frames_in_flight =
        m_swap_chain.createSwapChainFrames(m_render_way_storage);
}

void
RenderManager::shutdown()
{
}
// ----------------------- //
//
// --------- draw -------- //

void
RenderManager::draw(const Renderer& renderer)
{
    frame_number = (frame_number + 1) % max_frames_in_flight;
}

// ----------------------- //
}; // namespace render
}; // namespace kusengine
