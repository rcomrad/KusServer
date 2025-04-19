#ifndef RENDER_PASS_HPP
#define RENDER_PASS_HPP

#include "engine/pipeline/graphics_pipeline.hpp"

namespace kusengine
{
class RenderPass
{
public:
    RenderPass() = default;

    bool create(const vk::Device& logical_device,
                        const vk::PipelineLayout& pipeline_layout,
                        vk::Format swap_chain_format,
                        const vk::Extent2D& extent);

    const vk::RenderPass& renderPass() const;

    const GraphicsPipeline& graphicsPipeline() const;

private:
    bool createRenderPass(const vk::Device& logical_device,
                          vk::Format swap_chain_format);

    vk::UniqueRenderPass m_render_pass;

    GraphicsPipeline m_graphics_pipeline;
};
}; // namespace kusengine

#endif // RENDER_PASS_HPP
