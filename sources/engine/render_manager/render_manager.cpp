#include "render_manager.hpp"

#include <iostream>

#include "engine/render_manager/device/device.hpp"
#include "engine/window/window.hpp"

#define COMPILE_SHADERS 1

namespace kusengine::render
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

    m_camera_manager.setup(window_extent.width, window_extent.height);

    m_shader_manager.setup(COMPILE_SHADERS);

    m_instance.create("KusEngine");

    m_swap_chain.createSurface(window, m_instance);

    DEVICE_INSTANCE.create(m_instance, m_swap_chain.surface());

    m_swap_chain.create(window_extent.width, window_extent.height);

    COMMAND_POOL.create();

    m_descriptor_manager.setup();

    m_render_system.setup(m_descriptor_manager, m_shader_manager,
                          m_swap_chain.extent(), m_swap_chain.format());

    max_frames_in_flight = m_swap_chain.createSwapChainFrames(
        m_render_system, m_descriptor_manager);

    frame_number = 0;

    m_texture_manager.loadTextures("engine_textures/texture_paths.json",
                                   m_descriptor_manager);

    m_mesh_manager.loadMeshes();

    // camera
    m_ubo.camera_matrix = {1.f};
}

void
RenderManager::shutdown()
{
}
// ----------------------- //
//
// --------- draw -------- //

void
RenderManager::draw(BasicScene* const basic_scene)
{

    auto& upd_frame = m_swap_chain.getFrame(frame_number);

    upd_frame.waitForFence();

    // upd data
    m_ubo.camera_matrix =
        m_camera_manager.getCurrentCamera().get()->recalculate();

    upd_frame.updateUBO(m_ubo);
    basic_scene->updMbddFrame(upd_frame);

    auto acquire_res = LOGICAL_DEVICE_INSTANCE.acquireNextImageKHR(
        m_swap_chain.swapchain(), UINT64_MAX,
        upd_frame.synControl().imageAvailable(), nullptr);

    uint32_t image_index = acquire_res.value;

    // record part
    auto& upd_cmd = upd_frame.commandBuffer();

    auto binding_draw_lambda = [&scene    = basic_scene,
                                &rend_sys = m_render_system, &frame = upd_frame,
                                &cmd = upd_cmd]()
    {
        auto& layout = rend_sys.bindPipeline("default_3d", cmd);
        scene->bind(cmd);
        frame.bind(cmd, layout);
        scene->draw(cmd, layout);
    };

    m_render_system.execute(upd_frame, "default", upd_cmd, binding_draw_lambda);

    // submit part

    upd_frame.submitCommandBuffer();

    // record part

    vk::PresentInfoKHR presentInfo = {};
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores    = upd_frame.synControl().signalSemaphores();

    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains    = &m_swap_chain.swapchain();
    presentInfo.pImageIndices  = &image_index;

    auto result = DEVICE_INSTANCE.getQueue("present").presentKHR(presentInfo);

    if (result != vk::Result::eSuccess)
    {
        std::cout << "not success present\n";
    }

    frame_number = (frame_number + 1) % max_frames_in_flight;
}

// ----------------------- //
//
// ------ resources ------ //
const Texture* const
RenderManager::getResourceImpl(ChooseResType<Texture>&& rs,
                               const std::string& key) const
{
    return m_texture_manager.getTexture(key);
} // texture

const Mesh<Vertex2DP1UV1>* const
RenderManager::getResourceImpl(ChooseResType<Mesh<Vertex2DP1UV1>>&& rs,
                               const std::string& key) const
{
    return m_mesh_manager.getMesh<Vertex2DP1UV1>(key);
} // mesh<vertex 2d>

const Mesh<Vertex3DP1UV1>* const
RenderManager::getResourceImpl(ChooseResType<Mesh<Vertex3DP1UV1>>&& rs,
                               const std::string& key) const
{
    return m_mesh_manager.getMesh<Vertex3DP1UV1>(key);
} // mesh<vertex 3d>

// ----------------------- //
//
// ------- camera ---------//

CameraManager&
RenderManager::camera()
{
    return m_camera_manager;
}

// ----------------------- //

}; // namespace kusengine::render
