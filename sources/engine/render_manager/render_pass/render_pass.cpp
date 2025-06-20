#include "render_pass.hpp"

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/vertex/vertex.hpp"

namespace kusengine
{
namespace render
{

const vk::RenderPass&
RenderPass::renderPass() const
{
    return m_render_pass.get();
}

void
RenderPass::createRenderPass(vk::Format swap_chain_format)
{
    vk::AttachmentDescription colorAttachment = {};
    colorAttachment.flags          = vk::AttachmentDescriptionFlags();
    colorAttachment.format         = swap_chain_format;
    colorAttachment.samples        = vk::SampleCountFlagBits::e1;
    colorAttachment.loadOp         = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp        = vk::AttachmentStoreOp::eStore;
    colorAttachment.stencilLoadOp  = vk::AttachmentLoadOp::eDontCare;
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachment.initialLayout  = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout    = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment              = 0;
    colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::SubpassDescription subpass = {};
    subpass.flags                  = vk::SubpassDescriptionFlags();
    subpass.pipelineBindPoint      = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount   = 1;
    subpass.pColorAttachments      = &colorAttachmentRef;

    vk::RenderPassCreateInfo renderpassInfo = {};
    renderpassInfo.flags                    = vk::RenderPassCreateFlags();
    renderpassInfo.attachmentCount          = 1;
    renderpassInfo.pAttachments             = &colorAttachment;
    renderpassInfo.subpassCount             = 1;
    renderpassInfo.pSubpasses               = &subpass;

    m_render_pass =
        LOGICAL_DEVICE_INSTANCE.createRenderPassUnique(renderpassInfo);
}

void
RenderPass::init(vk::Format swap_chain_format)
{
    createRenderPass(swap_chain_format);
}
}; // namespace render
}; // namespace kusengine
