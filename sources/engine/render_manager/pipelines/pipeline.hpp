#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <vulkan/vulkan.hpp>

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/shaders/shaders/shader.hpp"

namespace kusengine
{
namespace render
{

class DescriptorManager;

struct PipelineConfigInfo
{
    vk::Extent2D extent;
    std::string vertex_shader_path;
    std::string fragment_shader_path;
};

class Pipeline
{
public:
    Pipeline() = default;
    void createPipelineLayout(const DescriptorManager& descriptor_manager);

    template <typename VertexType>
    void init(const PipelineConfigInfo& pipeline_config_info,
              const vk::RenderPass& render_pass,
              const DescriptorManager& descriptor_manager);

    const vk::Pipeline& pipeline() const noexcept;
    const vk::PipelineLayout& layout() const noexcept;

private:
    template <typename BindingDescType, typename AttributeDescType>
    vk::PipelineVertexInputStateCreateInfo vertexInputState(
        const BindingDescType& vertex_binding_description,
        const AttributeDescType& vertex_attribute_description);

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

template <typename BindingDescType, typename AttributeDescType>
vk::PipelineVertexInputStateCreateInfo
Pipeline::vertexInputState(
    const BindingDescType& vertex_binding_description,
    const AttributeDescType& vertex_attribute_description)
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

template <typename VertexType>
void
Pipeline::init(const PipelineConfigInfo& pipeline_config_info,
               const vk::RenderPass& render_pass,
               const DescriptorManager& descriptor_manager)
{
    ////////////////////
    createPipelineLayout(descriptor_manager);

    vk::GraphicsPipelineCreateInfo create_pipeline_info{};
    create_pipeline_info.flags = vk::PipelineCreateFlags();

    std::vector<vk::PipelineShaderStageCreateInfo> shader_stages;

    // Vertex Input
    auto& vertex_instance = VertexType::Description::getInstance();

    auto vertex_binding_description = vertex_instance.getBindingDescription();
    auto attributes = vertex_instance.getAttributeDescriptions();

    auto vertex_input =
        vertexInputState(vertex_binding_description, attributes);

    create_pipeline_info.pVertexInputState = &vertex_input;

    // input Assembly
    auto input_assembly = inputAssemblyState();

    create_pipeline_info.pInputAssemblyState = &input_assembly;

    // Vertex Shader

    vk::ShaderModule vertex_shader_module(
        shader::createShaderModule(pipeline_config_info.vertex_shader_path));

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

    vk::ShaderModule fragment_shader_module(
        shader::createShaderModule(pipeline_config_info.fragment_shader_path));

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

    // // Extra stuff
    create_pipeline_info.basePipelineHandle = nullptr;

    //  Make the Pipeline

    m_pipeline =
        LOGICAL_DEVICE_INSTANCE
            .createGraphicsPipelineUnique(nullptr, create_pipeline_info)
            .value;

    shader::destroyShaderModule(vertex_shader_module);

    shader::destroyShaderModule(fragment_shader_module);
}
}; // namespace render
}; // namespace kusengine

#endif // PIPELINE_HPP
