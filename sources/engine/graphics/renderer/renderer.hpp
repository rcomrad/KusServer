#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <mutex>

#include "engine/graphics/commands/command_pool.hpp"
#include "engine/graphics/descriptors/descriptor_manager.hpp"
#include "engine/graphics/device/device.hpp"
#include "engine/graphics/instance/instance.hpp"
#include "engine/graphics/scene/scene.hpp"
#include "engine/graphics/textures/texture_storage.hpp"

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

    void drawFrame(Window& window, const Scene& scene);

    bool initRenderer(Window& window);

    vk::Extent2D swapchainExtent() const;

    void loadTextures();

private:
    int max_frames_in_flight;
    int frame_number;

    Instance m_instance;

    SwapChain m_swap_chain;

    RenderPass m_render_pass;
    // PipleinLayout

    bool createPipelineLayout();

    vk::UniquePipelineLayout m_pipeline_layout;

    // Descriptors
    DescriptorManager m_descriptor_manager;
};

}; // namespace kusengine
#endif // RENDERER_HPP
