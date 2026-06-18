#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/logic/device.hpp"
#include "engine/vk_converter.hpp"
#include "kernel/framework/variable/include_me.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace engine::graphics
{

struct SimplePushConstantData
{
    glm::vec2 offset;
    alignas(16) glm::vec3 color;
};

class GraphicsPipeline
{

public:
    GraphicsPipeline(logic::Device a_logic_device,
                     vk::RenderPass a_render_pass,
                     vk::ShaderModule a_vert_smodule,
                     vk::ShaderModule a_frag_smodule);

    inline auto& getLayout()
    {
        return m_pipeline_layout;
    }

    inline auto& get()
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
