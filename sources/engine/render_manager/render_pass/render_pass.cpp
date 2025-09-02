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
    // -- color -- //

    vk::AttachmentDescription color_attachment{};
    color_attachment.flags          = vk::AttachmentDescriptionFlags();
    color_attachment.format         = render_pass_info.swap_chain_format;
    color_attachment.samples        = vk::SampleCountFlagBits::e1;
    color_attachment.loadOp         = vk::AttachmentLoadOp::eClear;
    color_attachment.storeOp        = vk::AttachmentStoreOp::eStore;
    color_attachment.stencilLoadOp  = vk::AttachmentLoadOp::eDontCare;
    color_attachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    color_attachment.initialLayout  = vk::ImageLayout::eUndefined;
    color_attachment.finalLayout    = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentReference color_attachment_ref{};
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout     = vk::ImageLayout::eColorAttachmentOptimal;

    // ----------- //
    // -- depth -- //
    vk::AttachmentDescription depth_attachment{};
    depth_attachment.format        = vk::Format::eD32Sfloat;
    depth_attachment.loadOp        = vk::AttachmentLoadOp::eClear;
    depth_attachment.storeOp       = vk::AttachmentStoreOp::eDontCare;
    depth_attachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    depth_attachment.initialLayout = vk::ImageLayout::eUndefined;
    depth_attachment.finalLayout =
        vk::ImageLayout::eDepthStencilAttachmentOptimal;

    vk::AttachmentReference depth_attachment_ref{};
    depth_attachment_ref.attachment = 1;
    depth_attachment_ref.layout =
        vk::ImageLayout::eDepthStencilAttachmentOptimal;

    // subpass //
    vk::SubpassDescription subpass{};
    subpass.flags                   = vk::SubpassDescriptionFlags();
    subpass.pipelineBindPoint       = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount    = 1;
    subpass.pColorAttachments       = &color_attachment_ref;
    subpass.pDepthStencilAttachment = &depth_attachment_ref;

    vk::RenderPassCreateInfo renderpass_info{};
    renderpass_info.flags           = vk::RenderPassCreateFlags();
    renderpass_info.attachmentCount = 2;

    vk::AttachmentDescription attachments[] = {color_attachment,
                                               depth_attachment};

    renderpass_info.pAttachments = attachments;
    renderpass_info.subpassCount = 1;
    renderpass_info.pSubpasses   = &subpass;

    m_render_pass =
        LOGICAL_DEVICE_INSTANCE.createRenderPassUnique(renderpass_info);
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

    std::array<vk::ClearValue, 2> clear_values{};

    clear_values[0].color        = vk::ClearColorValue{0.4f, 0.3f, 0.2f, 1.0f};
    clear_values[1].depthStencil = vk::ClearDepthStencilValue{1.0f, 0};

    renderPassInfo.clearValueCount = clear_values.size();

    renderPassInfo.pClearValues = clear_values.data();

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
