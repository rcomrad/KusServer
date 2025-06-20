#ifndef RENDER_WAY_HPP
#define RENDER_WAY_HPP

#include "engine/render_manager/descriptors/descriptor_manager.hpp"
#include "engine/render_manager/pipelines/pipeline.hpp"
#include "engine/render_manager/render_pass/render_pass.hpp"

namespace kusengine
{
namespace render
{
class RenderWay
{
public:
    RenderWay() = default;

    template <typename VertexType>
    void init(vk::Format format,
              const PipelineConfigInfo& pipeline_config_info,
              const std::vector<std::vector<DescriptorBindingData>>& bindings);

    const vk::RenderPass& renderPass() const noexcept;

    const DescriptorManager& descManager() const noexcept;

private:
    RenderPass m_render_pass;

    Pipeline m_pipeline;

    DescriptorManager m_descriptor_manager;
};

template <typename VertexType>
void
RenderWay::init(vk::Format format,
                const PipelineConfigInfo& pipeline_config_info,
                const std::vector<std::vector<DescriptorBindingData>>& bindings)
{
    m_descriptor_manager.init(bindings);
    m_render_pass.init(format);
    m_pipeline.init<VertexType>(
        pipeline_config_info, m_render_pass.renderPass(), m_descriptor_manager);
}

}; // namespace render
}; // namespace kusengine

#endif // RENDER_WAY_HPP
