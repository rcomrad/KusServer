#include "render_way.hpp"

namespace kusengine
{
namespace render
{
const vk::RenderPass&
RenderWay::renderPass() const noexcept
{
    return m_render_pass.renderPass();
}

const DescriptorManager&
RenderWay::descManager() const noexcept
{
    return m_descriptor_manager;
}
}; // namespace render
}; // namespace kusengine
