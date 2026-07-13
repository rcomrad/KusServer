#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/utils/vk_converter.hpp"

namespace gpu
{

namespace logic
{
class Device;
}

namespace pipeline
{

class RenderPass : public vk::RenderPass
{
public:
    RenderPass(logic::Device& a_device, vk::Format a_format);
    ~RenderPass();

    HOLY_TRINITY_NOCOPY(RenderPass);
    VK_CONVERTER(vk::RenderPass);

    vk::RenderPassBeginInfo getBeginInfo(vk::Framebuffer a_framebuffer);

private:
    logic::Device& m_device;
    vk::ClearValue m_clear_value;

    static vk::RenderPass create(logic::Device& a_device, vk::Format a_format);

    static std::vector<vk::AttachmentReference> createAttachmentReference();

    static std::vector<vk::AttachmentDescription> createAttachmentDescription(
        vk::Format a_format);
    static std::vector<vk::SubpassDescription> createSubpassDescription(
        const std::vector<vk::AttachmentReference>& a_attachment_ref);
    static std::vector<vk::SubpassDependency> createSubpassDependency();
};

} // namespace pipeline

} // namespace gpu
