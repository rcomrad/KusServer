#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/shaders/shader_manager.hpp"

namespace kusengine
{
namespace render
{

class DescriptorManager;

struct PipelineConfigInfo
{
    vk::UniquePipelineLayout pipeline_layout;
    vk::Extent2D extent;
    ShaderType vertex_shader_type;
    ShaderType fragment_shader_type;

    vk::Bool32 depth_test_enable = vk::False;

    vk::VertexInputBindingDescription vertex_binding_description;
    std::vector<vk::VertexInputAttributeDescription>
        vertex_attribute_descriptions;
};

class Pipeline
{
public:
    Pipeline(PipelineConfigInfo&& pipeline_config_info,
             const vk::RenderPass& render_pass,
             const ShaderManager& shader_manager);

    void create(PipelineConfigInfo&& pipeline_config_info,
                const vk::RenderPass& render_pass,
                const ShaderManager&
                    shader_manager); // rvalue because uniq pipeline layout

    void bind(const vk::CommandBuffer& cmd) const;

    const vk::PipelineLayout& layout() const noexcept;

private:
    vk::PipelineVertexInputStateCreateInfo vertexInputState(
        const vk::VertexInputBindingDescription& vertex_binding_description,
        const std::vector<vk::VertexInputAttributeDescription>&
            vertex_attribute_description);

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
