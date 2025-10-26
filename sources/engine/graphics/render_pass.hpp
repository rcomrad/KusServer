#pragma once

#include <vulkan/vulkan.hpp>

namespace engine::graphics
{

class RenderPass
{
public:
    RenderPass(vk::Device a_logic_device, vk::Format a_format);

    vk::RenderPassBeginInfo getBeginInfo(vk::Framebuffer a_framebuffer);

    inline auto& get()
    {
        return *m_render_pass;
    }

private:
    vk::UniqueRenderPass m_render_pass;

    std::vector<vk::AttachmentReference> createAttachmentReference() const;

    std::vector<vk::AttachmentDescription> createAttachmentDescription(
        vk::Format a_format) const;
    std::vector<vk::SubpassDescription> createSubpassDescription() const;
    std::vector<vk::SubpassDependency> createSubpassDependency() const;
};

} // namespace engine::graphics
