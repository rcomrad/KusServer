#include "graphics_pipeline.hpp"

#include <iostream>

namespace kusengine
{

const vk::Pipeline&
GraphicsPipeline::pipeline() const
{
    return m_pipeline.get();
}

bool
GraphicsPipeline::configureStages(
    std::vector<vk::PipelineShaderStageCreateInfo>& shader_stages)
{
    return true;
}

vk::PipelineInputAssemblyStateCreateInfo
GraphicsPipeline::inputAssemblyState()
{
    vk::PipelineInputAssemblyStateCreateInfo input_assembly_info;
    input_assembly_info.flags    = vk::PipelineInputAssemblyStateCreateFlags();
    input_assembly_info.topology = vk::PrimitiveTopology::eTriangleList;
    return input_assembly_info;
}

vk::PipelineViewportStateCreateInfo
GraphicsPipeline::viewportState(const vk::Extent2D& extent,
                                vk::Viewport& viewport_dst,
                                vk::Rect2D& scissor_dst)
{
    viewport_dst.x        = 0.0f;
    viewport_dst.y        = 0.0f;
    viewport_dst.width    = extent.width;
    viewport_dst.height   = extent.height;
    viewport_dst.minDepth = 0.0f;
    viewport_dst.maxDepth = 1.0f;

    scissor_dst.offset.x = 0.0f;
    scissor_dst.offset.y = 0.0f;
    scissor_dst.extent   = extent;

    vk::PipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.flags         = vk::PipelineViewportStateCreateFlags();
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &viewport_dst;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &scissor_dst;

    return viewport_state;
}

vk::PipelineRasterizationStateCreateInfo
GraphicsPipeline::rasterizerState()
{
    vk::PipelineRasterizationStateCreateInfo rasterizer;

    rasterizer.flags = vk::PipelineRasterizationStateCreateFlags();
    rasterizer.depthClampEnable =
        VK_FALSE; // discard out of bounds fragments, don't clamp them
    rasterizer.rasterizerDiscardEnable =
        VK_FALSE; // This flag would disable fragment output
    rasterizer.polygonMode = vk::PolygonMode::eFill;
    rasterizer.lineWidth   = 1.0f;
    rasterizer.cullMode    = vk::CullModeFlagBits::eBack;
    rasterizer.frontFace   = vk::FrontFace::eClockwise;
    rasterizer.depthBiasEnable =
        VK_FALSE; // Depth bias can be useful in shadow maps.

    return rasterizer;
}

vk::PipelineMultisampleStateCreateInfo
GraphicsPipeline::multisamplingState()
{
    vk::PipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.flags = vk::PipelineMultisampleStateCreateFlags();
    multisampling.sampleShadingEnable  = VK_FALSE;
    multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
    return multisampling;
}

vk::PipelineColorBlendStateCreateInfo
GraphicsPipeline::colorBlendState(
    vk::PipelineColorBlendAttachmentState& color_blend_attachment)
{

    color_blend_attachment.colorWriteMask =
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    color_blend_attachment.blendEnable = VK_FALSE;

    vk::PipelineColorBlendStateCreateInfo color_blending = {};
    color_blending.flags             = vk::PipelineColorBlendStateCreateFlags();
    color_blending.logicOpEnable     = VK_FALSE;
    color_blending.logicOp           = vk::LogicOp::eCopy;
    color_blending.attachmentCount   = 1;
    color_blending.pAttachments      = &color_blend_attachment;
    color_blending.blendConstants[0] = 0.0f;
    color_blending.blendConstants[1] = 0.0f;
    color_blending.blendConstants[2] = 0.0f;
    color_blending.blendConstants[3] = 0.0f;

    return color_blending;
}

vk::PipelineShaderStageCreateInfo
GraphicsPipeline::vertexShaderinfo(vk::ShaderStageFlagBits flag,
                                   const vk::ShaderModule& shader_module)
{
    vk::PipelineShaderStageCreateInfo vertex_shader_info = {};
    vertex_shader_info.flags  = vk::PipelineShaderStageCreateFlags();
    vertex_shader_info.stage  = flag;
    vertex_shader_info.module = shader_module;
    vertex_shader_info.pName  = "main";
    return vertex_shader_info;
}

}; // namespace kusengine
