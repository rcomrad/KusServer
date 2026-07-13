#pragma once

#include <vector>

#include "graphic_pipeline.hpp"
#include "image_collection.hpp"
#include "render_pass.hpp"
#include "shader.hpp"
#include "swap_chain.hpp"

namespace gpu
{

namespace logic
{
class Device;
}

namespace command
{
class DrawCommand;
}

namespace window
{
class Surface;
class SurfaceCharacteristics;
} // namespace window

namespace pipeline
{

class Manager
{
public:
    Manager(logic::Device a_device,
            window::Surface& a_surface,
            const window::SurfaceCharacteristics& a_characteristic);

    void bindToNextImage(command::DrawCommand& a_cmd_buff);

    inline auto getLayout()
    {
        return m_graphics_pipeline.getLayout();
    }

    inline auto getDescSetLayout()
    {
        return m_graphics_pipeline.getDescSetLayout();
    }

    SwapChain& getSwapChain();

private:
    SwapChain m_swap_chain;
    RenderPass m_render_pass;
    ImageCollection m_image_collection;
    std::vector<Shader> m_shaiders;
    GraphicsPipeline m_graphics_pipeline;
};

} // namespace pipeline

} // namespace gpu
