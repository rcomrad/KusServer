#include "render_pass.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/logic/device.hpp"
#include "gpu/utils/variable.hpp"

gpu::pipeline::RenderPass::RenderPass(logic::Device& a_device,
                                      vk::Format a_format)
    : vk::RenderPass(create(a_device, a_format)),
      m_device(a_device),
      m_clear_value(vk::ClearColorValue{1.0f, 0.0f, 0.0f, 0.0f})
{
}

vk::RenderPass
gpu::pipeline::RenderPass::create(logic::Device& a_device, vk::Format a_format)
{
    SCOPED_TRACE_INIT("render pass");

    vk::RenderPassCreateInfo info;

    auto attachment  = createAttachmentDescription(a_format);
    auto ref         = createAttachmentReference();
    auto description = createSubpassDescription(ref);
    auto dependency  = createSubpassDependency();

    info.setAttachments(attachment)
        .setSubpasses(description)
        .setDependencies(dependency);

    return a_device.createRenderPass(info);
}

gpu::pipeline::RenderPass::~RenderPass()
{
    SCOPED_TRACE_TERM("render pass");
    m_device.destroyRenderPass(*static_cast<vk::RenderPass*>(this));
}

vk::RenderPassBeginInfo
gpu::pipeline::RenderPass::getBeginInfo(vk::Framebuffer a_framebuffer)
{
    LOG_SPAM("getBeginInfo");

    core::IntVar m_width(VAR_NAME_FRAME_WIDTH);
    core::IntVar m_height(VAR_NAME_FRAME_HEIGHT);

    vk::RenderPassBeginInfo rp_begin_info;
    rp_begin_info.setRenderPass(*this)
        .setRenderArea(vk::Rect2D(vk::Offset2D(0, 0),
                                  vk::Extent2D(m_width.get(), m_height.get())))
        .setClearValueCount(1)
        .setPClearValues(&m_clear_value)
        .setFramebuffer(a_framebuffer);

    return rp_begin_info;
}

std::vector<vk::AttachmentReference>
gpu::pipeline::RenderPass::createAttachmentReference()
{
    std::vector<vk::AttachmentReference> result;

    result.emplace_back()
        .setAttachment(0) // vk::False // 0 // AttachmentUnused
        .setLayout(vk::ImageLayout::eColorAttachmentOptimal);

    return result;
}

std::vector<vk::AttachmentDescription>
gpu::pipeline::RenderPass::createAttachmentDescription(vk::Format a_format)
{
    std::vector<vk::AttachmentDescription> result;

    result.emplace_back()
        .setFormat(a_format)
        .setSamples(vk::SampleCountFlagBits::e1)
        .setLoadOp(vk::AttachmentLoadOp::eClear)
        .setStoreOp(vk::AttachmentStoreOp::eStore)
        .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
        .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
        .setInitialLayout(vk::ImageLayout::eUndefined)
        .setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

    return result;
}

std::vector<vk::SubpassDescription>
gpu::pipeline::RenderPass::createSubpassDescription(
    const std::vector<vk::AttachmentReference>& a_attachment_ref)
{
    std::vector<vk::SubpassDescription> result;

    result.emplace_back()
        .setColorAttachments(a_attachment_ref)
        .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics);

    return result;
}

std::vector<vk::SubpassDependency>
gpu::pipeline::RenderPass::createSubpassDependency()
{
    std::vector<vk::SubpassDependency> result;

    result.emplace_back()
        .setSrcSubpass(vk::SubpassExternal)
        .setSrcStageMask(vk::PipelineStageFlagBits::eBottomOfPipe)
        .setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
        .setSrcAccessMask(vk::AccessFlagBits::eMemoryRead)
        .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentRead |
                          vk::AccessFlagBits::eColorAttachmentWrite)
        .setDependencyFlags(vk::DependencyFlagBits::eByRegion);

    result.emplace_back()
        .setDstSubpass(vk::SubpassExternal)
        .setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
        .setDstStageMask(vk::PipelineStageFlagBits::eBottomOfPipe)
        .setSrcAccessMask(vk::AccessFlagBits::eColorAttachmentRead |
                          vk::AccessFlagBits::eColorAttachmentWrite)
        .setDstAccessMask(vk::AccessFlagBits::eMemoryRead)
        .setDependencyFlags(vk::DependencyFlagBits::eByRegion);

    return result;
}
