#pragma once

#include <vulkan/vulkan.hpp>

#include "kernel/framework/variable/include_me.hpp"

namespace engine::graphics
{

class GraphicsPipeline
{

public:
    GraphicsPipeline(vk::Device a_logic_device,
                     vk::RenderPass a_render_pass,
                     vk::ShaderModule a_vert_smodule,
                     vk::ShaderModule a_frag_smodule);

    auto& get()
    {
        return *m_pipeline[0];
    }

private:
    vk::UniquePipelineLayout m_pipeline_layout;
    std::vector<vk::UniquePipeline> m_pipeline;

    static std::vector<vk::PipelineShaderStageCreateInfo> createShaderStageInfo(
        vk::ShaderModule a_vert_smodule,
        vk::ShaderModule a_frag_smodule);
    static vk::PipelineVertexInputStateCreateInfo createVertexInputInfo();
    static vk::PipelineInputAssemblyStateCreateInfo createAssemblyStateInfo();
    static vk::PipelineViewportStateCreateInfo createViewportStateInfo();
    static vk::PipelineRasterizationStateCreateInfo
    createRasterizationStateInfo();
    static vk::PipelineMultisampleStateCreateInfo createMultisampleStateInfo();
    static vk::PipelineColorBlendStateCreateInfo createColorBlendStateInfo();
};

} // namespace engine::graphics
