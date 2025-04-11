#include "graphics_pipeline.hpp"

#include "shaders/shaders/shader.hpp"
namespace kusengine
{
bool
GraphicsPipeline::createGraphicsPipeline(const vk::Device& logical_device)
{
    vk::GraphicsPipelineCreateInfo create_pipeline_info{};
    create_pipeline_info.flags = vk::PipelineCreateFlags();

    std::vector<vk::PipelineShaderStageCreateInfo> shader_stages;

    // Vertex Input

    vk::PipelineVertexInputStateCreateInfo vertex_input_info{};
    vertex_input_info.flags = vk::PipelineVertexInputStateCreateFlags();
    vertex_input_info.vertexBindingDescriptionCount   = 0;
    vertex_input_info.vertexAttributeDescriptionCount = 0;
    create_pipeline_info.pVertexInputState            = &vertex_input_info;

    // input Assembly
    vk::PipelineInputAssemblyStateCreateInfo input_assembly_info;
    input_assembly_info.flags    = vk::PipelineInputAssemblyStateCreateFlags();
    input_assembly_info.topology = vk::PrimitiveTopology::eTriangleList;
    create_pipeline_info.pInputAssemblyState = &input_assembly_info;

    // Vertex Shader

    vk::UniqueShaderModule vertex_shader_module(
        Shader::getInstance().createShaderModule("", logical_device));

    vk::PipelineShaderStageCreateInfo vertex_shader_info = {};
    vertex_shader_info.flags  = vk::PipelineShaderStageCreateFlags();
    vertex_shader_info.stage  = vk::ShaderStageFlagBits::eVertex;
    vertex_shader_info.module = vertex_shader_module.get();
    vertex_shader_info.pName  = "main";
    shader_stages.push_back(vertex_shader_info);
}
}; // namespace kusengine
