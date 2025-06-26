#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/shaders/shaders/shader.hpp"

namespace kusengine
{
namespace render
{

class DescriptorManager;

struct PipelineConfigInfo
{
    vk::UniquePipelineLayout pipeline_layout;
    vk::Extent2D extent;
    std::string vertex_shader_path;
    std::string fragment_shader_path;

    vk::VertexInputBindingDescription vertex_binding_description;
    std::vector<vk::VertexInputAttributeDescription>
        vertex_attribute_descriptions;
};

class Pipeline
{
public:
    Pipeline(PipelineConfigInfo&& pipeline_config_info,
             const vk::RenderPass& render_pass);

    void create(PipelineConfigInfo&& pipeline_config_info,
                const vk::RenderPass&
                    render_pass); // rvalue because uniq pipeline layout

    void bind(const vk::CommandBuffer& cmd) const;

    const vk::PipelineLayout& layout() const noexcept;

private:

    vk::PipelineVertexInputStateCreateInfo vertexInputState(
        const vk::VertexInputBindingDescription& vertex_binding_description,
        const std::vector<vk::VertexInputAttributeDescription>& vertex_attribute_description);

    vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState();
    vk::PipelineRasterizationStateCreateInfo rasterizerState();
    vk::PipelineMultisampleStateCreateInfo multisamplingState();
    vk::PipelineColorBlendStateCreateInfo colorBlendState(
        vk::PipelineColorBlendAttachmentState& color_blend_attachment);

    vk::PipelineViewportStateCreateInfo viewportState(
        const vk::Extent2D& extent,
        vk::Viewport& viewport_dst,
        vk::Rect2D& scissor_dst);

    vk::PipelineShaderStageCreateInfo vertexShaderinfo(
        vk::ShaderStageFlagBits flag,
        const vk::ShaderModule& shader_module);

    vk::UniquePipeline m_pipeline;

    // Pipeline Layout
    vk::UniquePipelineLayout m_layout;
};

}; // namespace render
}; // namespace kusengine

#endif // PIPELINE_HPP
