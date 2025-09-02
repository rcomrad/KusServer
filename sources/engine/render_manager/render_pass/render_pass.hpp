#ifndef RENDER_PASS_HPP
#define RENDER_PASS_HPP

#include "engine/render_manager/pipelines/pipeline.hpp"

namespace kusengine
{
namespace render
{

struct RenderPassConfigInfo
{
    vk::Format swap_chain_format;
};

class RenderPass
{
public:
    RenderPass() = default;

    RenderPass(const RenderPassConfigInfo& render_pass_info);

    void create(const RenderPassConfigInfo& render_pass_info);

    const vk::RenderPass& renderPass() const;

    void begin(const vk::CommandBuffer& cmd,
               const vk::Framebuffer& framebuffer,
               const vk::Extent2D& extent);

    void end(const vk::CommandBuffer& cmd);

private:
    vk::UniqueRenderPass m_render_pass;
};
}; // namespace render
}; // namespace kusengine

#endif // RENDER_PASS_HPP
