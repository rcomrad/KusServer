#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <functional>
#include <memory>
#include <unordered_map>

#include "engine/render_manager/descriptors/descriptor_manager.hpp"
#include "engine/render_manager/material/material.hpp"
#include "engine/render_manager/model/model_data/model_upd_data.hpp"
#include "engine/render_manager/pipelines/pipeline.hpp"
#include "engine/render_manager/render_pass/render_pass.hpp"
#include "engine/render_manager/shaders/shader_manager.hpp"
#include "engine/render_manager/swap_chain/swap_chain_frame.hpp"
#include "engine/render_manager/vertex/vertex.hpp"

#include "pipeline_key.hpp"

namespace kusengine::render
{

class RenderSystem
{
public:
    void setup(const DescriptorManager& desc_manager,
               const ShaderManager& shader_manager,
               const vk::Extent2D& extent,
               const vk::Format& format);

    void registerPipeline(VertexType vertex_type,
                          ModelUpdData::Type model_upd_data_type,
                          Material::Type material_type,
                          std::string_view render_pass,
                          PipelineConfigInfo&& pipeline_info,
                          const ShaderManager& shader_manager);

    void registerRenderPass(std::string_view key,
                            const RenderPassConfigInfo& render_pass_info);

    void setExtent(const vk::Extent2D& extent);

    void translateRenderPassesToFrame(SwapChainFrame& frame) const;

    const vk::PipelineLayout& bindPipeline(
        VertexType vertex_type,
        ModelUpdData::Type model_upd_data_type,
        Material::Type material_type,
        const vk::CommandBuffer& cmd) const&;

    const vk::PipelineLayout& getLayout(PipelineLayoutType) const&;

    void execute(const std::string& render_pass_name,
                 std::function<void()> binding,
                 const vk::CommandBuffer& cmd,
                 const vk::Framebuffer& frame_buffer) const;

private:
    vk::UniquePipelineLayout makePipelineLayout(int count,
                                                vk::DescriptorSetLayout* data);

    void setupDefaultPipelines(const DescriptorManager& desc_manager,
                               const ShaderManager& shader_manager);
    void setupDefaultRenderPass();

    std::unordered_map<PipelineLayoutType, vk::UniquePipelineLayout>
        m_layout_storage;

    std::unordered_map<PipelineKey, std::unique_ptr<Pipeline>> m_pipelines;

    std::unordered_map<std::string, std::unique_ptr<RenderPass>>
        m_render_passes;

    vk::Extent2D m_extent;
    vk::Format m_format;
};

} // namespace kusengine::render

#endif // RENDER_SYSTEM_HPP
