#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <functional>
#include <memory>
#include <unordered_map>

#include "engine/render_manager/descriptors/descriptor_manager.hpp"
#include "engine/render_manager/pipelines/pipeline.hpp"
#include "engine/render_manager/render_pass/render_pass.hpp"
#include "engine/render_manager/swap_chain/swap_chain_frame.hpp"

namespace kusengine::render
{
class RenderSystem
{
public:
    void setup(const DescriptorManager& desc_manager,
               const vk::Extent2D& extent,
               const vk::Format& format);

    void registerPipeline(std::string_view key,
                          std::string_view render_pass,
                          PipelineConfigInfo&& pipeline_info);

    void registerRenderPass(std::string_view key,
                            const RenderPassConfigInfo& render_pass_info);

    void execute(const SwapChainFrame& swap_chain,
                 const std::string& pass_name,
                 const vk::CommandBuffer& cmd,
                 const std::function<void()>& bd_lambda);

    void setExtent(const vk::Extent2D& extent);

    void translateRenderPassesToFrame(SwapChainFrame& frame) const;

    const vk::PipelineLayout& bindPipeline(const std::string& key, const vk::CommandBuffer& cmd) const &;

private:
    vk::UniquePipelineLayout makePipelineLayout(int count,
                                                vk::DescriptorSetLayout* data);

    void setupDefaultPipeline(const DescriptorManager& desc_manager);
    void setupDefaultRenderPass();

    std::unordered_map<std::string, std::unique_ptr<Pipeline>> m_pipelines;

    std::unordered_map<std::string, std::unique_ptr<RenderPass>>
        m_render_passes;

    vk::Extent2D m_extent;
    vk::Format m_format;
};

} // namespace kusengine::render

#endif // RENDER_SYSTEM_HPP
