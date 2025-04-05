#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

#include "device.hpp"

namespace kusengine
{

struct PipelineConfigInfo
{
    PipelineConfigInfo();
    vk::Viewport viewport;
    vk::Rect2D scissor;
    vk::PipelineViewportStateCreateInfo viewport_info;
    vk::PipelineInputAssemblyStateCreateInfo input_assembly_info;
    vk::PipelineRasterizationStateCreateInfo rasterization_info;
    vk::PipelineMultisampleStateCreateInfo multisample_info;
    vk::PipelineColorBlendAttachmentState color_blend_attachment;
    vk::PipelineColorBlendStateCreateInfo color_blend_info;
    vk::PipelineDepthStencilStateCreateInfo depth_stencil_info;
    vk::PipelineLayout pipeline_layout;
    vk::RenderPass render_pass;
    uint32_t subpass;
};

class Pipeline
{
public:
    Pipeline(const Pipeline&)            = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    Pipeline() = default;

    void bind(vk::CommandBuffer command_buffer);

    void initPipeline(const std::string& vertex_shader_path,
                      const std::string& fragment_shader_path,
                      Device* device_ptr,
                      const PipelineConfigInfo& info);

    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width,
                                                        uint32_t heigth);

private:
    void createShaderModule(const std::vector<char>& code,
                            vk::ShaderModule& shader_module);

    vk::Pipeline m_pipeline;

    vk::ShaderModule m_vertex_shader_module;
    vk::ShaderModule m_fragment_shader_module;

    Device* m_device_ptr;
};
}; // namespace kusengine

#endif // PIPELINE_HPP
