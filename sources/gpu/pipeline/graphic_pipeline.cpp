#include "graphic_pipeline.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

#include "gpu/logic/device.hpp"
#include "gpu/sprite/sprite_push_data.hpp"
#include "gpu/utils/variable.hpp"

#include "render_pass.hpp"

gpu::pipeline::GraphicsPipeline::GraphicsPipeline(logic::Device& a_logic_device,
                                                  RenderPass& a_render_pass,
                                                  Shader& a_vert_smodule,
                                                  Shader& a_frag_smodule)
{
    SCOPED_TRACE_INIT("graphics pipeline");

    auto push_const   = createPushConstant();
    m_desc_set_layout = createDescriptorSetLayout(a_logic_device);
    m_pipeline_layout =
        createPipelineLayout(a_logic_device, *m_desc_set_layout, push_const);

    auto stages = createShaderStageInfo(a_vert_smodule, a_frag_smodule);

    auto vertex_input_state = createVertexInputInfo();

    auto input_assembly_state = createAssemblyStateInfo();

    auto viewport       = createViewport();
    auto scissors       = createScissors();
    auto viewport_state = createViewportStateInfo(viewport, scissors);

    auto rasterization_state = createRasterizationStateInfo();
    auto multisample_state   = createMultisampleStateInfo();
    auto attachments         = createColorBlendAttachments();
    auto color_blend_state   = createColorBlendStateInfo(attachments);

    std::vector<vk::GraphicsPipelineCreateInfo> pipeline_info;
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

std::vector<vk::PushConstantRange>
gpu::pipeline::GraphicsPipeline::createPushConstant()
{
    SCOPED_TRACE_CREATE("push constant");

    std::vector<vk::PushConstantRange> result;
    result.emplace_back()
        .setStageFlags(vk::ShaderStageFlagBits::eVertex |
                       vk::ShaderStageFlagBits::eFragment)
        .setOffset(0)
        .setSize(sizeof(sprite::SpritePushData));
    return result;
}

vk::UniqueDescriptorSetLayout
gpu::pipeline::GraphicsPipeline::createDescriptorSetLayout(
    logic::Device& a_logic_device)
{
    SCOPED_TRACE_CREATE("DescriptorSetLayout");

    std::vector<vk::DescriptorSetLayoutBinding> set_layout_binding;
    set_layout_binding.emplace_back()
        .setBinding(0)
        .setDescriptorCount(1)
        .setDescriptorType(vk::DescriptorType::eCombinedImageSampler)
        .setStageFlags(vk::ShaderStageFlagBits::eFragment);

    vk::DescriptorSetLayoutCreateInfo layout_info;
    layout_info.setBindings(set_layout_binding);

    return a_logic_device.createDescriptorSetLayoutUnique(layout_info);
}

vk::UniquePipelineLayout
gpu::pipeline::GraphicsPipeline::createPipelineLayout(
    logic::Device& a_logic_device,
    vk::DescriptorSetLayout& a_desc_set_layout,
    const std::vector<vk::PushConstantRange>& a_push_const)
{
    SCOPED_TRACE_CREATE("PipelineLayout");

    std::vector<vk::DescriptorSetLayout> layout_array = {a_desc_set_layout};

    vk::PipelineLayoutCreateInfo layout_info;
    layout_info.setPushConstantRanges(a_push_const).setSetLayouts(layout_array);
    return a_logic_device.createPipelineLayoutUnique(layout_info);
}

std::vector<vk::PipelineShaderStageCreateInfo>
gpu::pipeline::GraphicsPipeline::createShaderStageInfo(Shader& a_vert_smodule,
                                                       Shader& a_frag_smodule)
{
    SCOPED_TRACE_CREATE("PipelineShaderStageCreateInfo");

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
gpu::pipeline::GraphicsPipeline::createVertexInputInfo()
{
    SCOPED_TRACE_CREATE("PipelineVertexInputStateCreateInfo");

    vk::PipelineVertexInputStateCreateInfo result;
    return result;
}

vk::PipelineInputAssemblyStateCreateInfo
gpu::pipeline::GraphicsPipeline::createAssemblyStateInfo()
{
    SCOPED_TRACE_CREATE("PipelineInputAssemblyStateCreateInfo");

    vk::PipelineInputAssemblyStateCreateInfo result;
    result.setTopology(vk::PrimitiveTopology::eTriangleList)
        .setPrimitiveRestartEnable(vk::False);
    return result;
}

std::vector<vk::Viewport>
gpu::pipeline::GraphicsPipeline::createViewport()
{
    SCOPED_TRACE_CREATE("viewport");

    core::IntVar width(VAR_NAME_FRAME_WIDTH);
    core::IntVar height(VAR_NAME_FRAME_HEIGHT);

    std::vector<vk::Viewport> result;
    result.emplace_back()
        .setX(0)
        .setY(0)
        .setWidth(width.get())
        .setHeight(height.get())
        .setMinDepth(0)
        .setMaxDepth(1);

    return result;
}

std::vector<vk::Rect2D>
gpu::pipeline::GraphicsPipeline::createScissors()
{
    SCOPED_TRACE_CREATE("scissors");

    core::IntVar width(VAR_NAME_FRAME_WIDTH);
    core::IntVar height(VAR_NAME_FRAME_HEIGHT);

    std::vector<vk::Rect2D> result;
    result.emplace_back()
        .setOffset(vk::Offset2D(0, 0))
        .setExtent(vk::Extent2D(width.get(), height.get()));

    return result;
}

vk::PipelineViewportStateCreateInfo
gpu::pipeline::GraphicsPipeline::createViewportStateInfo(
    const std::vector<vk::Viewport>& a_viewport,
    const std::vector<vk::Rect2D>& a_scissors)
{
    SCOPED_TRACE_CREATE("PipelineViewportStateCreateInfo");

    vk::PipelineViewportStateCreateInfo result;
    result.setViewports(a_viewport).setScissors(a_scissors);
    return result;
}

vk::PipelineRasterizationStateCreateInfo
gpu::pipeline::GraphicsPipeline::createRasterizationStateInfo()
{
    SCOPED_TRACE_CREATE("PipelineRasterizationStateCreateInfo");

    vk::PipelineRasterizationStateCreateInfo result;
    result.setPolygonMode(vk::PolygonMode::eFill)
        .setCullMode(vk::CullModeFlagBits::eNone)
        .setFrontFace(vk::FrontFace::eCounterClockwise)
        .setLineWidth(1);
    return result;
}

vk::PipelineMultisampleStateCreateInfo
gpu::pipeline::GraphicsPipeline::createMultisampleStateInfo()
{
    SCOPED_TRACE_CREATE("PipelineMultisampleStateCreateInfo");

    vk::PipelineMultisampleStateCreateInfo result;
    result.setRasterizationSamples(vk::SampleCountFlagBits::e1)
        .setSampleShadingEnable(vk::False)
        .setMinSampleShading(1);
    return result;
}

std::vector<vk::PipelineColorBlendAttachmentState>
gpu::pipeline::GraphicsPipeline::createColorBlendAttachments()
{
    SCOPED_TRACE_CREATE("PipelineColorBlendAttachmentState");

    std::vector<vk::PipelineColorBlendAttachmentState> result;
    result.emplace_back().setBlendEnable(vk::False).setColorWriteMask(
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);
    return result;
}

vk::PipelineColorBlendStateCreateInfo
gpu::pipeline::GraphicsPipeline::createColorBlendStateInfo(
    const std::vector<vk::PipelineColorBlendAttachmentState>& a_attachments)
{
    SCOPED_TRACE_CREATE("PipelineColorBlendStateCreateInfo");

    vk::PipelineColorBlendStateCreateInfo result;
    result.setLogicOpEnable(vk::False)
        .setLogicOp(vk::LogicOp::eCopy)
        .setAttachments(a_attachments);
    return result;
}
