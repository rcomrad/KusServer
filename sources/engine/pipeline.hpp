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
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo viewport_info;
    VkPipelineInputAssemblyStateCreateInfo input_assembly_info;
    VkPipelineRasterizationStateCreateInfo rasterization_info;
    VkPipelineMultisampleStateCreateInfo multisample_info;
    VkPipelineColorBlendAttachmentState color_blend_attachment;
    VkPipelineColorBlendStateCreateInfo color_blend_info;
    VkPipelineDepthStencilStateCreateInfo depth_stencil_info;
    VkPipelineLayout pipeline_layout;
    VkRenderPass render_pass;
    uint32_t subpass;
};

class Pipeline
{
public:
    Pipeline(const Pipeline&)            = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    ~Pipeline();

    Pipeline() = default;

    void bind(VkCommandBuffer command_buffer);

    void initPipeline(const std::string& vertex_shader_path,
                      const std::string& fragment_shader_path,
                      Device* device_ptr,
                      const PipelineConfigInfo& info);

    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width,
                                                        uint32_t heigth);

private:
    std::vector<char> readFile(const std::string& filepath);

    void createShaderModule(const std::vector<char>& code,
                            VkShaderModule* shader_module);

    VkPipeline m_pipeline;

    VkShaderModule m_vertex_shader_module;
    VkShaderModule m_fragment_shader_module;

    Device* m_device_ptr;
};
}; // namespace kusengine

#endif // PIPELINE_HPP
