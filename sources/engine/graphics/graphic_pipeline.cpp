#include "graphic_pipeline.hpp"

#include "engine/logic/vertix.hpp"
#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

namespace engine::graphics
{

GraphicsPipeline::GraphicsPipeline(logic::Device a_logic_device,
                                   vk::RenderPass a_render_pass,
                                   vk::ShaderModule a_vert_smodule,
                                   vk::ShaderModule a_frag_smodule)
{
    SCOPED_TRACE_INIT("graphics pipeline");

    static std::vector<vk::PushConstantRange> push_const_range;
    push_const_range.clear();
    push_const_range.emplace_back()
        .setStageFlags(vk::ShaderStageFlagBits::eVertex |
                       vk::ShaderStageFlagBits::eFragment)
        .setOffset(0)
        .setSize(sizeof(SimplePushConstantData));

    vk::PipelineLayoutCreateInfo layout_info;
    layout_info.setPushConstantRanges(push_const_range);
    m_pipeline_layout = a_logic_device.createPipelineLayoutUnique(layout_info);

    auto stages = createShaderStageInfo(a_vert_smodule, a_frag_smodule);
    auto vertex_input_state   = createVertexInputInfo();
    auto input_assembly_state = createAssemblyStateInfo();
    auto viewport_state       = createViewportStateInfo();
    auto rasterization_state  = createRasterizationStateInfo();
    auto multisample_state    = createMultisampleStateInfo();
    auto color_blend_state    = createColorBlendStateInfo();

    static std::vector<vk::GraphicsPipelineCreateInfo> pipeline_info;
    pipeline_info.clear();
    pipeline_info.emplace_back()
        .setStages(stages)
        .setPVertexInputState(&vertex_input_state)
        .setPInputAssemblyState(&input_assembly_state)
        .setPViewportState(&viewport_state)
        .setPRasterizationState(&rasterization_state)
        .setPMultisampleState(&multisample_state)
        .setPColorBlendState(&color_blend_state)
        .setLayout(*m_pipeline_layout)
        .setRenderPass(a_render_pass)
        .setBasePipelineIndex(-1);

    auto temp_res = a_logic_device.createGraphicsPipelinesUnique(VK_NULL_HANDLE,
                                                                 pipeline_info);
    if (temp_res.result != vk::Result::eSuccess)
    {
        // TODO: move to_string inside THROW
        THROW("Unable to create graphic pipeline: ", to_string(temp_res.result))
    }
    m_pipeline = std::move(temp_res.value);
}

std::vector<vk::PipelineShaderStageCreateInfo>
GraphicsPipeline::createShaderStageInfo(vk::ShaderModule a_vert_smodule,
                                        vk::ShaderModule a_frag_smodule)
{
    std::vector<vk::PipelineShaderStageCreateInfo> result;

    vk::PipelineShaderStageCreateInfo first;
    first.setStage(vk::ShaderStageFlagBits::eVertex)
        .setModule(a_vert_smodule)
        .setPName("main");
    result.emplace_back(first);

    vk::PipelineShaderStageCreateInfo second;
    second.setStage(vk::ShaderStageFlagBits::eFragment)
        .setModule(a_frag_smodule)
        .setPName("main");
    result.emplace_back(second);

    return result;
}

vk::PipelineVertexInputStateCreateInfo
GraphicsPipeline::createVertexInputInfo()
{
    vk::PipelineVertexInputStateCreateInfo result;

    static auto binding_desc   = logic::Vertex::getBindingDescriptions();
    static auto attribute_desc = logic::Vertex::getAttributeDescriptions();

    result.setVertexBindingDescriptions(binding_desc)
        .setVertexAttributeDescriptions(attribute_desc);

    return result;
}

vk::PipelineInputAssemblyStateCreateInfo
GraphicsPipeline::createAssemblyStateInfo()
{
    vk::PipelineInputAssemblyStateCreateInfo result;
    result.setTopology(vk::PrimitiveTopology::eTriangleList)
        .setPrimitiveRestartEnable(vk::False);
    return result;
}

vk::PipelineViewportStateCreateInfo
GraphicsPipeline::createViewportStateInfo()
{
    core::IntVar width("win_width");
    core::IntVar height("win_height");

    static std::vector<vk::Viewport> viewports;
    viewports.clear();
    viewports.emplace_back()
        .setX(0)
        .setY(0)
        .setWidth(width.get())
        .setHeight(height.get())
        .setMinDepth(0)
        .setMaxDepth(1);

    static std::vector<vk::Rect2D> scissors;
    scissors.clear();
    scissors = {vk::Rect2D(vk::Offset2D(0, 0),
                           vk::Extent2D(width.get(), height.get()))};

    vk::PipelineViewportStateCreateInfo result;
    result.setViewports(viewports).setScissors(scissors);
    return result;
}

vk::PipelineRasterizationStateCreateInfo
GraphicsPipeline::createRasterizationStateInfo()
{
    vk::PipelineRasterizationStateCreateInfo result;
    result.setPolygonMode(vk::PolygonMode::eFill)
        .setCullMode(vk::CullModeFlagBits::eNone)
        .setFrontFace(vk::FrontFace::eCounterClockwise)
        .setLineWidth(1);
    return result;
}

vk::PipelineMultisampleStateCreateInfo
GraphicsPipeline::createMultisampleStateInfo()
{
    vk::PipelineMultisampleStateCreateInfo result;
    result.setRasterizationSamples(vk::SampleCountFlagBits::e1)
        .setSampleShadingEnable(vk::False)
        .setMinSampleShading(1);
    return result;
}

vk::PipelineColorBlendStateCreateInfo
GraphicsPipeline::createColorBlendStateInfo()
{
    static std::vector<vk::PipelineColorBlendAttachmentState> blend_attachmens;
    blend_attachmens.clear();
    blend_attachmens.emplace_back().setBlendEnable(vk::False).setColorWriteMask(
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

    vk::PipelineColorBlendStateCreateInfo result;
    result.setLogicOpEnable(vk::False)
        .setLogicOp(vk::LogicOp::eCopy)
        .setAttachments(blend_attachmens);
    return result;
}

} // namespace engine::graphics
