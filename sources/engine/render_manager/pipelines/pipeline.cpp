#include "pipeline.hpp"

#include <iostream>

#include "engine/render_manager/descriptors/descriptor_manager.hpp"

namespace kusengine
{
namespace render
{

void
Pipeline::bind(const vk::CommandBuffer& cmd) const
{
    cmd.bindPipeline(vk::PipelineBindPoint::eGraphics, m_pipeline.get());
}

Pipeline::Pipeline(PipelineConfigInfo&& pipeline_config_info,
                   const vk::RenderPass& render_pass,
                   const ShaderManager& shader_manager)
{
    create(std::move(pipeline_config_info), render_pass, shader_manager);
}

const vk::PipelineLayout&
Pipeline::layout() const noexcept
{
    return m_layout.get();
}

// void
// Pipeline::createPipelineLayout(const DescriptorManager& descriptor_manager)
// {
//     vk::PipelineLayoutCreateInfo layout_info;
//     layout_info.flags = vk::PipelineLayoutCreateFlags();
//     layout_info.setLayoutCount =
//         descriptor_manager.descriptorSetLayoutVector().size();
//     layout_info.pSetLayouts =
//         descriptor_manager.descriptorSetLayoutVector().data();
//     layout_info.pushConstantRangeCount = 0;

//     m_layout =
//     LOGICAL_DEVICE_INSTANCE.createPipelineLayoutUnique(layout_info);
// }

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
    color_blend_attachment.blendEnable = vk::True;
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
    color_blending.logicOpEnable     = vk::False;
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

void
Pipeline::create(PipelineConfigInfo&& pipeline_config_info,
                 const vk::RenderPass& render_pass,
                 const ShaderManager& shader_manager)
{
    ////////////////////
    m_layout = std::move(pipeline_config_info.pipeline_layout);

    vk::GraphicsPipelineCreateInfo create_pipeline_info{};
    create_pipeline_info.flags = vk::PipelineCreateFlags();

    std::vector<vk::PipelineShaderStageCreateInfo> shader_stages;

    // Vertex Input

    auto vertex_binding_description =
        pipeline_config_info.vertex_binding_description;
    auto attributes = pipeline_config_info.vertex_attribute_descriptions;

    auto vertex_input =
        vertexInputState(vertex_binding_description, attributes);

    create_pipeline_info.pVertexInputState = &vertex_input;

    // input Assembly
    auto input_assembly = inputAssemblyState();

    create_pipeline_info.pInputAssemblyState = &input_assembly;

    // Vertex Shader

    vk::ShaderModule vertex_shader_module(shader_manager.createShaderModule(
        pipeline_config_info.vertex_shader_type));

    shader_stages.push_back(vertexShaderinfo(vk::ShaderStageFlagBits::eVertex,
                                             vertex_shader_module));

    // Viewport and Scissor

    vk::Viewport viewport;
    vk::Rect2D scissor;

    auto viewport_state =
        viewportState(pipeline_config_info.extent, viewport, scissor);

    create_pipeline_info.pViewportState = &viewport_state;

    // Rasterizer
    auto rasterizer = rasterizerState();

    create_pipeline_info.pRasterizationState = &rasterizer;

    // Fragment Shader

    vk::ShaderModule fragment_shader_module(shader_manager.createShaderModule(
        pipeline_config_info.fragment_shader_type));

    shader_stages.push_back(vertexShaderinfo(vk::ShaderStageFlagBits::eFragment,
                                             fragment_shader_module));

    create_pipeline_info.stageCount = shader_stages.size();
    create_pipeline_info.pStages    = shader_stages.data();

    // Multisampling
    auto multisampling = multisamplingState();

    create_pipeline_info.pMultisampleState = &multisampling;

    // Color Blend
    vk::PipelineColorBlendAttachmentState color_blend_attachment{};
    auto color_blending = colorBlendState(color_blend_attachment);

    create_pipeline_info.pColorBlendState = &color_blending;

    // Renderpass

    create_pipeline_info.renderPass = render_pass;
    create_pipeline_info.subpass    = 0;

    // Extra stuff
    create_pipeline_info.basePipelineHandle = nullptr;

    // Depth Stencil
    vk::PipelineDepthStencilStateCreateInfo depth_stencil_info{};
    depth_stencil_info.depthTestEnable = pipeline_config_info.depth_test_enable;
    depth_stencil_info.depthWriteEnable  = vk::True;
    depth_stencil_info.depthCompareOp    = vk::CompareOp::eLess;
    depth_stencil_info.stencilTestEnable = vk::True;

    create_pipeline_info.pDepthStencilState = &depth_stencil_info;

    //  Make the Pipeline
    create_pipeline_info.layout = m_layout.get();

    m_pipeline =
        LOGICAL_DEVICE_INSTANCE
            .createGraphicsPipelineUnique(nullptr, create_pipeline_info)
            .value;

    shader_manager.destroyShaderModule(vertex_shader_module);

    shader_manager.destroyShaderModule(fragment_shader_module);
}

vk::PipelineVertexInputStateCreateInfo
Pipeline::vertexInputState(
    const vk::VertexInputBindingDescription& vertex_binding_description,
    const std::vector<vk::VertexInputAttributeDescription>&
        vertex_attribute_description)
{
    vk::PipelineVertexInputStateCreateInfo vertex_input_info{};
    vertex_input_info.flags = vk::PipelineVertexInputStateCreateFlags();

    vertex_input_info.vertexBindingDescriptionCount = 1;
    vertex_input_info.pVertexBindingDescriptions = &vertex_binding_description;

    vertex_input_info.vertexAttributeDescriptionCount =
        vertex_attribute_description.size();
    vertex_input_info.pVertexAttributeDescriptions =
        vertex_attribute_description.data();

    return vertex_input_info;
}

}; // namespace render
}; // namespace kusengine
