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
RenderManager::setup(const kusengine::Window& window)
{
    m_current_frame_number = 0;

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

    m_max_frames_in_flight =
        m_swap_chain.createSwapChainFrames(m_render_system);

    m_texture_manager.loadTextures(m_descriptor_manager);

    m_material_manager.setup(m_texture_manager);

    m_mesh_manager.setup(m_material_manager);
}

void
RenderManager::shutdown()
{
}

const MeshManager&
RenderManager::meshManager() const noexcept
{
    return m_mesh_manager;
}

const DescriptorManager&
RenderManager::descriptorManager() const noexcept
{
    return m_descriptor_manager;
}

int
RenderManager::frameCount() const noexcept
{
    return m_max_frames_in_flight;
}

int
RenderManager::getCurrentFrameNumber() const noexcept
{
    return m_current_frame_number;
}

// ----------------------- //
//
// --------- draw -------- //

void
RenderManager::render(Scene& scene)
{
    auto& upd_frame = m_swap_chain.getFrame(m_current_frame_number);

    upd_frame.waitForFence();

    // upd data

    m_ubo.camera_matrix = m_camera_manager.getCurrentCamera()->getMatrix();

    scene.updateBuffers(m_ubo, m_current_frame_number);
    //

    auto acquire_res = LOGICAL_DEVICE_INSTANCE.acquireNextImageKHR(
        m_swap_chain.swapchain(), UINT64_MAX,
        upd_frame.synControl().imageAvailable(), nullptr);

    uint32_t image_index = acquire_res.value;

    // record part

    auto& upd_cmd = upd_frame.commandBuffer();

    scene.draw(upd_cmd, m_render_system, m_current_frame_number,
               upd_frame); // begin renderpass and end

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

    m_current_frame_number =
        (m_current_frame_number + 1) % m_max_frames_in_flight;
}

// ----------------------- //
//
// ------ resources ------ //
// const Texture* const
// RenderManager::getResourceImpl(ChooseResType<Texture>&& rs,
//                                const std::string& key) const
// {
//     return m_texture_manager.getTexture(key);
// } // texture

// const Mesh<Vertex2DP1UV1>* const
// RenderManager::getResourceImpl(ChooseResType<Mesh<Vertex2DP1UV1>>&& rs,
//                                const std::string& key) const
// {
//     return m_mesh_manager.getMesh<Vertex2DP1UV1>(key);
// } // mesh<vertex 2d>

// const Mesh<Vertex3DP1UV1>* const
// RenderManager::getResourceImpl(ChooseResType<Mesh<Vertex3DP1UV1>>&& rs,
//                                const std::string& key) const
// {
//     return m_mesh_manager.getMesh<Vertex3DP1UV1>(key);
// } // mesh<vertex 3d>

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
