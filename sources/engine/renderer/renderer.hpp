#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <mutex>

#include "engine/commands/command_pool.hpp"
#include "engine/device/device.hpp"
#include "engine/instance/instance.hpp"

#include "render_pass.hpp"
#include "swap_chain.hpp"
#include "synchronization_control.hpp"
#include "engine/mesh/triangle_mesh.hpp"

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
    void drawFrameImpl(Window& window);

    int max_frames_in_flight;
    int frame_number;

    Instance m_instance;

    Device m_device;

    SwapChain m_swap_chain;

    RenderPass m_render_pass;

    TriangleMesh m_triangle_mesh;

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
