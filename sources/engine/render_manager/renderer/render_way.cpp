#include "render_way.hpp"

namespace kusengine
{
namespace render
{
const vk::RenderPass&
RenderWay::renderPass() const noexcept
{
    return m_render_pass.renderPass();
}

const DescriptorManager&
RenderWay::descManager() const noexcept
{
    return m_descriptor_manager;
}

void
RenderWay::bind(const vk::CommandBuffer& command_buffer,
                const std::vector<vk::DescriptorSet>& desc_sets) const
{
    command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics,
                                m_pipeline.pipeline());

    command_buffer.bindDescriptorSets(
        vk::PipelineBindPoint::eGraphics, m_pipeline.layout(), 0u,
        desc_sets.size(), desc_sets.data(), 0, nullptr); // frame resources
}
}; // namespace render
}; // namespace kusengine
