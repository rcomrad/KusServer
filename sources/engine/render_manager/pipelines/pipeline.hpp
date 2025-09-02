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

enum class PipelineLayoutType
{
    v_UBO_x_STORAGE__f_COMBINED_IMAGE_SAMPLER
};

class DescriptorManager;

struct PipelineConfigInfo
{
    vk::PipelineLayout pipeline_layout;
    vk::Extent2D extent;
    ShaderType vertex_shader_type;
    ShaderType fragment_shader_type;

    PipelineLayoutType pipeline_layout_type;

    vk::Bool32 depth_test_enable = vk::False;

    vk::VertexInputBindingDescription vertex_binding_description;
    std::vector<vk::VertexInputAttributeDescription>
        vertex_attribute_descriptions;
};

class Pipeline
{
public:
    Pipeline(const PipelineConfigInfo& pipeline_config_info,
             const vk::RenderPass& render_pass,
             const ShaderManager& shader_manager);

    void create(const PipelineConfigInfo& pipeline_config_info,
                const vk::RenderPass& render_pass,
                const ShaderManager&
                    shader_manager); // rvalue because uniq pipeline layout

    void bind(const vk::CommandBuffer& cmd) const;

    PipelineLayoutType getPipeLayoutType() const noexcept;

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

    PipelineLayoutType m_pipeline_layout_type;
};

}; // namespace render
}; // namespace kusengine

#endif // PIPELINE_HPP
