#include "pipeline.hpp"

#include <iostream>

#include "engine/render_manager/descriptors/descriptor_manager.hpp"

namespace kusengine
{
namespace render
{
const vk::Pipeline&
Pipeline::pipeline() const noexcept
{
    return m_pipeline.get();
}

const vk::PipelineLayout&
Pipeline::layout() const noexcept
{
    return m_layout.get();
}

void
Pipeline::createPipelineLayout(const DescriptorManager& descriptor_manager)
{
    vk::PipelineLayoutCreateInfo layout_info;
    layout_info.flags = vk::PipelineLayoutCreateFlags();
    layout_info.setLayoutCount =
        descriptor_manager.descriptorSetLayoutVector().size();
    layout_info.pSetLayouts =
        descriptor_manager.descriptorSetLayoutVector().data();
    layout_info.pushConstantRangeCount = 0;

    m_layout = LOGICAL_DEVICE_INSTANCE.createPipelineLayoutUnique(layout_info);
}

vk::PipelineInputAssemblyStateCreateInfo
Pipeline::inputAssemblyState()
{
    vk::PipelineInputAssemblyStateCreateInfo input_assembly_info;
    input_assembly_info.flags    = vk::PipelineInputAssemblyStateCreateFlags();
    input_assembly_info.topology = vk::PrimitiveTopology::eTriangleList;
    return input_assembly_info;
}

vk::PipelineViewportStateCreateInfo
Pipeline::viewportState(const vk::Extent2D& extent,
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
Pipeline::rasterizerState()
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
Pipeline::multisamplingState()
{
    vk::PipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.flags = vk::PipelineMultisampleStateCreateFlags();
    multisampling.sampleShadingEnable  = VK_FALSE;
    multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;
    return multisampling;
}

vk::PipelineColorBlendStateCreateInfo
Pipeline::colorBlendState(
    vk::PipelineColorBlendAttachmentState& color_blend_attachment)
{
    color_blend_attachment.blendEnable = VK_TRUE;
    color_blend_attachment.colorWriteMask =
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    color_blend_attachment.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;

    color_blend_attachment.dstColorBlendFactor =
        vk::BlendFactor::eOneMinusSrcAlpha;

    color_blend_attachment.colorBlendOp        = vk::BlendOp::eAdd;
    color_blend_attachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
    color_blend_attachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
    color_blend_attachment.alphaBlendOp        = vk::BlendOp::eAdd;

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
Pipeline::vertexShaderinfo(vk::ShaderStageFlagBits flag,
                           const vk::ShaderModule& shader_module)
{
    vk::PipelineShaderStageCreateInfo vertex_shader_info = {};
    vertex_shader_info.flags  = vk::PipelineShaderStageCreateFlags();
    vertex_shader_info.stage  = flag;
    vertex_shader_info.module = shader_module;
    vertex_shader_info.pName  = "main";
    return vertex_shader_info;
}
}; // namespace render
}; // namespace kusengine
