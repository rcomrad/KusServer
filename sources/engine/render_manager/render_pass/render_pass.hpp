#ifndef RENDER_PASS_HPP
#define RENDER_PASS_HPP

#include "engine/render_manager/pipelines/pipeline.hpp"

namespace kusengine
{
namespace render
{
class RenderPass
{
public:
    RenderPass() = default;

    void init(vk::Format swap_chain_format);

    const vk::RenderPass& renderPass() const;

private:
    void createRenderPass(vk::Format swap_chain_format);

    vk::UniqueRenderPass m_render_pass;
};
}; // namespace render
}; // namespace kusengine

#endif // RENDER_PASS_HPP
