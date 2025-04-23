#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <mutex>

#include "engine/commands/command_pool.hpp"
#include "engine/device/device.hpp"
#include "engine/instance/instance.hpp"
#include "engine/mesh/mesh_storage.hpp"
#include "engine/scene/scene.hpp"

#include "render_pass.hpp"
#include "swap_chain.hpp"
#include "synchronization_control.hpp"

namespace kusengine
{

class Window;

class Renderer final
{
public:
    Renderer();

    template <typename... Args>
    void drawFrame(Args&&... args);

    bool initRenderer(Window& window);

    void deviceWaitIdle();

private:
    // void drawFrameImpl();
    void drawFrameImpl(Window& window, const Scene& scene);

    int max_frames_in_flight;
    int frame_number;

    Instance m_instance;

    SwapChain m_swap_chain;

    RenderPass m_render_pass;

    Device& device_ref;

    // Triangle
    MeshStorage<UniversalVertex> m_mesh_storage;

    //
    bool createPipelineLayout();

    vk::UniquePipelineLayout m_pipeline_layout;

    // Command-related variables

    CommandPool m_command_pool;
};

template <typename... Args>
void
Renderer::drawFrame(Args&&... args)
{
    drawFrameImpl(std::forward<Args>(args)...);
}

}; // namespace kusengine
#endif // RENDERER_HPP
