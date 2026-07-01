#pragma once

#include "kernel/framework/variable/include_me.hpp"
#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/logic/device.hpp"
#include "gpu/utils/vk_converter.hpp"

namespace gpu::pipeline
{

class GraphicsPipeline
{

public:
    GraphicsPipeline(logic::Device& a_logic_device,
                     vk::RenderPass a_render_pass,
                     vk::ShaderModule a_vert_smodule,
                     vk::ShaderModule a_frag_smodule);
    HOLY_TRINITY_NOCOPY(GraphicsPipeline);

    inline auto getLayout()
    {
        return *m_pipeline_layout;
    }

    inline auto getDescSetLayout()
    {
        return *m_desc_set_layout;
    }

    inline auto& get()
    {
        return *m_pipeline[0];
    }

private:
    vk::UniqueDescriptorSetLayout m_desc_set_layout;
    vk::UniquePipelineLayout m_pipeline_layout;
    std::vector<vk::UniquePipeline> m_pipeline;

    static std::vector<vk::PushConstantRange> createPushConstant();
    static vk::UniqueDescriptorSetLayout createDescriptorSetLayout(
        logic::Device& a_logic_device);
    static vk::UniquePipelineLayout createPipelineLayout(
        logic::Device& a_logic_device,
        vk::DescriptorSetLayout& a_desc_set_layout,
        const std::vector<vk::PushConstantRange>& a_push_const);

    static std::vector<vk::PipelineShaderStageCreateInfo> createShaderStageInfo(
        vk::ShaderModule a_vert_smodule,
        vk::ShaderModule a_frag_smodule);
    static vk::PipelineVertexInputStateCreateInfo createVertexInputInfo();
    static vk::PipelineInputAssemblyStateCreateInfo createAssemblyStateInfo();

    static std::vector<vk::Viewport> createViewport();
    static std::vector<vk::Rect2D> createScissors();
    static vk::PipelineViewportStateCreateInfo createViewportStateInfo(
        const std::vector<vk::Viewport>& a_viewport,
        const std::vector<vk::Rect2D>& a_scissors);

    static vk::PipelineRasterizationStateCreateInfo
    createRasterizationStateInfo();
    static vk::PipelineMultisampleStateCreateInfo createMultisampleStateInfo();

    static std::vector<vk::PipelineColorBlendAttachmentState>
    createColorBlendAttachments();
    static vk::PipelineColorBlendStateCreateInfo createColorBlendStateInfo(
        const std::vector<vk::PipelineColorBlendAttachmentState>&
            a_attachments);
};

} // namespace gpu::pipeline
