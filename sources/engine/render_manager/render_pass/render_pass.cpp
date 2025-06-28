#include "render_pass.hpp"

#include "engine/render_manager/device/device.hpp"
#include "engine/render_manager/vertex/vertex.hpp"

namespace kusengine
{
namespace render
{

RenderPass::RenderPass(const RenderPassConfigInfo& render_pass_info)
{
    create(render_pass_info);
}

const vk::RenderPass&
RenderPass::renderPass() const
{
    return m_render_pass.get();
}

void
RenderPass::create(const RenderPassConfigInfo& render_pass_info)
{
    vk::AttachmentDescription colorAttachment = {};
    colorAttachment.flags          = vk::AttachmentDescriptionFlags();
    colorAttachment.format         = render_pass_info.swap_chain_format;
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
RenderPass::begin(const vk::CommandBuffer& cmd,
                  const vk::Framebuffer& framebuffer,
                  const vk::Extent2D& extent)
{
    cmd.reset();

    vk::CommandBufferBeginInfo beginInfo = {};

    cmd.begin(beginInfo);

    vk::RenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.renderPass              = m_render_pass.get();
    renderPassInfo.framebuffer             = framebuffer;

    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent   = extent;

    renderPassInfo.clearValueCount = 1;
    vk::ClearValue clear_value{vk::ClearColorValue(0.f, 0.f, 0.f, 1.f)};

    renderPassInfo.pClearValues = &clear_value;

    cmd.beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);
}

void
RenderPass::end(const vk::CommandBuffer& cmd)
{
    cmd.endRenderPass();

    cmd.end();
}
}; // namespace render
}; // namespace kusengine
