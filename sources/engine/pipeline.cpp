#include "pipeline.hpp"

#include <fstream>

#include "utility/file_system/path_storage.hpp"

#include "model.hpp"

namespace kusengine
{

Pipeline::~Pipeline()
{
    vkDestroyShaderModule(m_device_ptr->device(), m_vertex_shader_module, NULL);
    vkDestroyShaderModule(m_device_ptr->device(), m_fragment_shader_module,
                          NULL);

    vkDestroyPipeline(m_device_ptr->device(), m_pipeline, nullptr);
}

PipelineConfigInfo
Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
{
    PipelineConfigInfo config_info{};

    config_info.input_assembly_info.sType =
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    config_info.input_assembly_info.topology =
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    config_info.input_assembly_info.primitiveRestartEnable = VK_FALSE;

    config_info.viewport.x        = 0.0f;
    config_info.viewport.y        = 0.0f;
    config_info.viewport.width    = static_cast<float>(width);
    config_info.viewport.height   = static_cast<float>(height);
    config_info.viewport.minDepth = 0.0f;
    config_info.viewport.maxDepth = 1.0f;

    config_info.scissor.offset = {0, 0};
    config_info.scissor.extent = {width, height};

    config_info.rasterization_info.sType =
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    config_info.rasterization_info.depthClampEnable        = VK_FALSE;
    config_info.rasterization_info.rasterizerDiscardEnable = VK_FALSE;
    config_info.rasterization_info.polygonMode     = VK_POLYGON_MODE_FILL;
    config_info.rasterization_info.lineWidth       = 1.0f;
    config_info.rasterization_info.cullMode        = VK_CULL_MODE_NONE;
    config_info.rasterization_info.frontFace       = VK_FRONT_FACE_CLOCKWISE;
    config_info.rasterization_info.depthBiasEnable = VK_FALSE;
    config_info.rasterization_info.depthBiasConstantFactor = 0.0f; // Optional
    config_info.rasterization_info.depthBiasClamp          = 0.0f; // Optional
    config_info.rasterization_info.depthBiasSlopeFactor    = 0.0f; // Optional

    config_info.multisample_info.sType =
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    config_info.multisample_info.sampleShadingEnable   = VK_FALSE;
    config_info.multisample_info.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    config_info.multisample_info.minSampleShading      = 1.0f;     // Optional
    config_info.multisample_info.pSampleMask           = nullptr;  // Optional
    config_info.multisample_info.alphaToCoverageEnable = VK_FALSE; // Optional
    config_info.multisample_info.alphaToOneEnable      = VK_FALSE; // Optional

    config_info.color_blend_attachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    config_info.color_blend_attachment.blendEnable = VK_FALSE;
    config_info.color_blend_attachment.srcColorBlendFactor =
        VK_BLEND_FACTOR_ONE; // Optional
    config_info.color_blend_attachment.dstColorBlendFactor =
        VK_BLEND_FACTOR_ZERO; // Optional
    config_info.color_blend_attachment.colorBlendOp =
        VK_BLEND_OP_ADD; // Optional
    config_info.color_blend_attachment.srcAlphaBlendFactor =
        VK_BLEND_FACTOR_ONE; // Optional
    config_info.color_blend_attachment.dstAlphaBlendFactor =
        VK_BLEND_FACTOR_ZERO; // Optional
    config_info.color_blend_attachment.alphaBlendOp =
        VK_BLEND_OP_ADD; // Optional

    config_info.color_blend_info.sType =
        VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    config_info.color_blend_info.logicOpEnable   = VK_FALSE;
    config_info.color_blend_info.logicOp         = VK_LOGIC_OP_COPY; // Optional
    config_info.color_blend_info.attachmentCount = 1;
    config_info.color_blend_info.pAttachments =
        &config_info.color_blend_attachment;
    config_info.color_blend_info.blendConstants[0] = 0.0f; // Optional
    config_info.color_blend_info.blendConstants[1] = 0.0f; // Optional
    config_info.color_blend_info.blendConstants[2] = 0.0f; // Optional
    config_info.color_blend_info.blendConstants[3] = 0.0f; // Optional

    config_info.depth_stencil_info.sType =
        VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    config_info.depth_stencil_info.depthTestEnable       = VK_TRUE;
    config_info.depth_stencil_info.depthWriteEnable      = VK_TRUE;
    config_info.depth_stencil_info.depthCompareOp        = VK_COMPARE_OP_LESS;
    config_info.depth_stencil_info.depthBoundsTestEnable = VK_FALSE;
    config_info.depth_stencil_info.minDepthBounds        = 0.0f; // Optional
    config_info.depth_stencil_info.maxDepthBounds        = 1.0f; // Optional
    config_info.depth_stencil_info.stencilTestEnable     = VK_FALSE;
    config_info.depth_stencil_info.front                 = {}; // Optional
    config_info.depth_stencil_info.back                  = {}; // Optional

    return config_info;
}

std::vector<char>
Pipeline::readFile(const std::string& filepath)
{
    std::string ENGINE_DIR = "C:/Users/arsbo/source/repos/KusServer/";

    std::string enginePath = ENGINE_DIR.data() + filepath;

    std::ifstream file{enginePath, std::ios::ate | std::ios::binary};

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

void
Pipeline::bind(VkCommandBuffer command_buffer)
{
    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      m_pipeline);
}

void
Pipeline::initPipeline(const std::string& vertex_shader_path,
                       const std::string& fragment_shader_path,
                       Device* device_ptr,
                       const PipelineConfigInfo& config_info)
{
    m_device_ptr = device_ptr;
    compileShaders(vertex_shader_path, fragment_shader_path);

    auto vertCode = readFile(vertex_shader_path);
    auto fragCode = readFile(fragment_shader_path);

    createShaderModule(vertCode, &m_vertex_shader_module);
    createShaderModule(fragCode, &m_fragment_shader_module);

    VkPipelineShaderStageCreateInfo shaderStages[2];
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module              = m_vertex_shader_module;
    shaderStages[0].pName               = "main";
    shaderStages[0].flags               = 0;
    shaderStages[0].pNext               = nullptr;
    shaderStages[0].pSpecializationInfo = nullptr;
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module              = m_fragment_shader_module;
    shaderStages[1].pName               = "main";
    shaderStages[1].flags               = 0;
    shaderStages[1].pNext               = nullptr;
    shaderStages[1].pSpecializationInfo = nullptr;

    auto bindingDescriptions   = Model::Vertex::getBindingDescriptions();
    auto attributeDescriptions = Model::Vertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexAttributeDescriptionCount =
        static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.vertexBindingDescriptionCount =
        static_cast<uint32_t>(bindingDescriptions.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
    vertexInputInfo.pVertexBindingDescriptions   = bindingDescriptions.data();

    VkPipelineViewportStateCreateInfo viewport_info{};
    viewport_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_info.viewportCount = 1;
    viewport_info.pViewports    = &config_info.viewport;
    viewport_info.scissorCount  = 1;
    viewport_info.pScissors     = &config_info.scissor;

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages    = shaderStages;
    pipelineInfo.pVertexInputState   = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &config_info.input_assembly_info;
    pipelineInfo.pViewportState      = &viewport_info; // ????????????????
    pipelineInfo.pRasterizationState = &config_info.rasterization_info;
    pipelineInfo.pMultisampleState   = &config_info.multisample_info;
    pipelineInfo.pColorBlendState    = &config_info.color_blend_info;
    pipelineInfo.pDepthStencilState  = &config_info.depth_stencil_info;
    pipelineInfo.pDynamicState       = nullptr;

    pipelineInfo.layout     = config_info.pipeline_layout;
    pipelineInfo.renderPass = config_info.render_pass;
    pipelineInfo.subpass    = config_info.subpass;

    pipelineInfo.basePipelineIndex  = -1;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    vkCreateGraphicsPipelines(device_ptr->device(), VK_NULL_HANDLE, 1,
                              &pipelineInfo, nullptr, &m_pipeline);
}

void
Pipeline::createShaderModule(const std::vector<char>& code,
                             VkShaderModule* shader_module)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode    = reinterpret_cast<const uint32_t*>(code.data());

    vkCreateShaderModule(m_device_ptr->device(), &createInfo, nullptr,
                         shader_module);
}

void
Pipeline::compileShaders(const std::string& vertex_shader_path,
                         const std::string& fragment_shader_path)
{
    // compile
}

}; // namespace kusengine
