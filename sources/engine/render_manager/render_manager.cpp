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

    m_descriptor_manager.setup();

    m_render_system.setup(m_descriptor_manager, m_swap_chain.extent(),
                          m_swap_chain.format());

    max_frames_in_flight = m_swap_chain.createSwapChainFrames(
        m_render_system, m_descriptor_manager);

    frame_number = 0;
}

void
RenderManager::shutdown()
{
}
// ----------------------- //
//
// --------- draw -------- //

void
RenderManager::registerScene(BasicScene* const basic_scene)
{
    basic_scene->registerThis(m_drawable_system_storage);
}

void
RenderManager::draw(BasicScene* const basic_scene)
{
    frame_number = (frame_number + 1) % max_frames_in_flight;

    // m_render_system.execute();

    // auto render_info = basic_scene->getRenderInfo();

    // basic_scene->draw()

    // auto render_info = renderer.getInfo();

    // m_swap_chain.drawFrame(frame_number, );
}

// ----------------------- //
}; // namespace render
}; // namespace kusengine
