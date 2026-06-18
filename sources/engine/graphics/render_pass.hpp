#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/logic/device.hpp"
#include "engine/vk_converter.hpp"

namespace engine::graphics
{

class RenderPass : public vk::RenderPass
{
public:
    RenderPass(logic::Device& a_device, vk::Format a_format);
    ~RenderPass();

    VK_CONVERTER(vk::RenderPass);

    vk::RenderPassBeginInfo getBeginInfo(vk::Framebuffer a_framebuffer);

private:
    // vk::UniqueRenderPass m_render_pass;
    logic::Device& m_device;

    vk::RenderPass create(logic::Device a_device, vk::Format a_format);

    std::vector<vk::AttachmentReference> createAttachmentReference() const;

    std::vector<vk::AttachmentDescription> createAttachmentDescription(
        vk::Format a_format) const;
    std::vector<vk::SubpassDescription> createSubpassDescription() const;
    std::vector<vk::SubpassDependency> createSubpassDependency() const;
};

} // namespace engine::graphics
