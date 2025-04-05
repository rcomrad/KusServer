#include "pipeline.hpp"

#include <fstream>
#include <iostream>

#include "utility/file_system/path_storage.hpp"

#include "engine_util.hpp"
#include "model.hpp"

namespace kusengine
{

PipelineConfigInfo::PipelineConfigInfo()
{
}

PipelineConfigInfo
Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
{
    PipelineConfigInfo config;

    // Input Assembly
    config.input_assembly_info =
        vk::PipelineInputAssemblyStateCreateInfo{}
            .setTopology(vk::PrimitiveTopology::eTriangleList)
            .setPrimitiveRestartEnable(false);

    // Viewport and Scissor

    config.viewport.setWidth(static_cast<float>(width))
        .setHeight(static_cast<float>(height))
        .setMaxDepth(1.0f)
        .setMinDepth(0.0f)
        .setX(0.0f)
        .setY(0.0f);

    config.scissor.setExtent({width, height}).setOffset({0, 0});

    config.viewport_info.setViewports(config.viewport)
        .setScissors(config.scissor);

    // Rasterization
    config.rasterization_info = vk::PipelineRasterizationStateCreateInfo{}
                                    .setDepthClampEnable(false)
                                    .setRasterizerDiscardEnable(false)
                                    .setPolygonMode(vk::PolygonMode::eFill)
                                    .setLineWidth(1.0f)
                                    .setCullMode(vk::CullModeFlagBits::eNone)
                                    .setFrontFace(vk::FrontFace::eClockwise)
                                    .setDepthBiasEnable(false);

    // Multisampling
    config.multisample_info =
        vk::PipelineMultisampleStateCreateInfo{}
            .setSampleShadingEnable(false)
            .setRasterizationSamples(vk::SampleCountFlagBits::e1);

    // Color Blending
    config.color_blend_attachment =
        vk::PipelineColorBlendAttachmentState{}
            .setColorWriteMask(vk::ColorComponentFlagBits::eR |
                               vk::ColorComponentFlagBits::eG |
                               vk::ColorComponentFlagBits::eB |
                               vk::ColorComponentFlagBits::eA)
            .setBlendEnable(false);

    config.color_blend_info =
        vk::PipelineColorBlendStateCreateInfo{}
            .setLogicOpEnable(false)
            .setAttachments(config.color_blend_attachment);

    // Depth Stencil
    config.depth_stencil_info = vk::PipelineDepthStencilStateCreateInfo{}
                                    .setDepthTestEnable(true)
                                    .setDepthWriteEnable(true)
                                    .setDepthCompareOp(vk::CompareOp::eLess)
                                    .setDepthBoundsTestEnable(false)
                                    .setStencilTestEnable(false);

    config.subpass = 0;

    return config;
}

void
Pipeline::bind(vk::CommandBuffer command_buffer)
{
    command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, m_pipeline);
}

void
Pipeline::initPipeline(const std::string& vertex_shader_path,
                       const std::string& fragment_shader_path,
                       Device* device_ptr,
                       const PipelineConfigInfo& config_info)
{
    m_device_ptr = device_ptr;

    // Read shader files
    auto vertCode = engine_util::readFile(vertex_shader_path);
    auto fragCode = engine_util::readFile(fragment_shader_path);

    auto viewportState = config_info.viewport_info;

    vk::PipelineViewportStateCreateInfo()
        .setScissorCount(1)
        .setPScissors(&config_info.scissor)
        .setViewportCount(1)
        .setPViewports(&config_info.viewport);

    createShaderModule(vertCode, m_vertex_shader_module);
    createShaderModule(fragCode, m_fragment_shader_module);

    // Create shader stages
    std::array<vk::PipelineShaderStageCreateInfo, 2> shaderStages = {
        vk::PipelineShaderStageCreateInfo()
            .setStage(vk::ShaderStageFlagBits::eVertex)
            .setModule(m_vertex_shader_module)
            .setPName("main"),
        vk::PipelineShaderStageCreateInfo()
            .setStage(vk::ShaderStageFlagBits::eFragment)
            .setModule(m_fragment_shader_module)
            .setPName("main")};

    // Get vertex descriptions
    auto bindingDescriptions   = Model::Vertex::getBindingDescriptions();
    auto attributeDescriptions = Model::Vertex::getAttributeDescriptions();

    // Vertex input state
    auto vertexInputInfo =
        vk::PipelineVertexInputStateCreateInfo()
            .setVertexBindingDescriptions(bindingDescriptions)
            .setVertexAttributeDescriptions(attributeDescriptions);

    // Viewport state

    // Pipeline creation
    auto pipelineInfo =
        vk::GraphicsPipelineCreateInfo()
            .setStages(shaderStages)
            .setPVertexInputState(&vertexInputInfo)
            .setPInputAssemblyState(&config_info.input_assembly_info)
            .setPViewportState(&viewportState)
            .setPRasterizationState(&config_info.rasterization_info)
            .setPMultisampleState(&config_info.multisample_info)
            .setPColorBlendState(&config_info.color_blend_info)
            .setPDepthStencilState(&config_info.depth_stencil_info)
            .setLayout(config_info.pipeline_layout)
            .setRenderPass(config_info.render_pass)
            .setSubpass(config_info.subpass);

    auto result =
        m_device_ptr->device().createGraphicsPipeline(nullptr, // Pipeline cache
                                                      pipelineInfo);
    m_pipeline = result.value;
}

void
Pipeline::createShaderModule(const std::vector<char>& code,
                             vk::ShaderModule& shader_module)
{
    vk::ShaderModuleCreateInfo createInfo(
        {},                                            // flags
        code.size(),                                   // codeSize
        reinterpret_cast<const uint32_t*>(code.data()) // pCode
    );

    shader_module = m_device_ptr->device().createShaderModule(createInfo);
}
}; // namespace kusengine
