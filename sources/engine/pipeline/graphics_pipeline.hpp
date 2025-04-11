#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <vulkan/vulkan.hpp>

namespace kusengine
{

struct PipelineConfigInfo
{
    vk::Viewport viewport;
    vk::Rect2D scissor;
    vk::PipelineViewportStateCreateInfo viewport_info;
    vk::PipelineInputAssemblyStateCreateInfo input_assembly_info;
    vk::PipelineRasterizationStateCreateInfo rasterization_info;
    vk::PipelineMultisampleStateCreateInfo multisample_info;
    vk::PipelineColorBlendAttachmentState color_blend_attachment;
    vk::PipelineColorBlendStateCreateInfo color_blend_info;
    vk::PipelineDepthStencilStateCreateInfo depth_stencil_info;
    vk::PipelineLayout pipeline_layout;
    vk::RenderPass render_pass;
    uint32_t subpass;
};

class GraphicsPipeline
{
public:
    GraphicsPipeline() = default;

    bool createGraphicsPipeline(const vk::Device& logical_device);

private:
    vk::UniquePipeline m_pipeline;
};
}; // namespace kusengine

#endif // PIPELINE_HPP
