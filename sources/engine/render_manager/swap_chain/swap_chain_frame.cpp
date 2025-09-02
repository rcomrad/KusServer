#include "swap_chain_frame.hpp"

#include <iostream>

#include "engine/render_manager/descriptors/descriptor_manager.hpp"

#include "swap_chain.hpp"
#include "synchronization_control.hpp"
namespace kusengine::render
{

const SynchronizationControl&
SwapChainFrame::synControl() const& noexcept
{
    return m_sync_control;
}

const vk::CommandBuffer&
SwapChainFrame::commandBuffer() const& noexcept
{
    return m_command_buffer.commandBuffer();
}

const vk::Framebuffer&
SwapChainFrame::getBuffer(const std::string& key) const&
{
    auto it = m_framebuffers.find(key);
    if (it == m_framebuffers.end())
    {
        throw std::exception("cant find frame buffer");
    }
    return it->second.get();
}

void
SwapChainFrame::setupDepth(const vk::Extent2D& extent)
{
    ImageConfigInfo image_config_info = {
        .format      = vk::Format::eD32Sfloat,
        .width       = extent.width,
        .height      = extent.height,
        .usage_flags = vk::ImageUsageFlagBits::eDepthStencilAttachment |
                       vk::ImageUsageFlagBits::eTransferDst |
                       vk::ImageUsageFlagBits::eSampled};

    m_depth_image.create(image_config_info);

    ImageViewConfigInfo image_view_config_info = {
        .aspect_mask = vk::ImageAspectFlagBits::eDepth};
    m_depth_image.createImageView(image_view_config_info);
}

void
SwapChainFrame::setupImages(const vk::Image& image,
                            const vk::Format& format,
                            const vk::Extent2D& extent)
{
    // view
    {
        vk::ImageViewCreateInfo create_image_view_info = {};
        create_image_view_info.image                   = image;
        create_image_view_info.viewType                = vk::ImageViewType::e2D;
        create_image_view_info.format                  = format;
        create_image_view_info.components.r = vk::ComponentSwizzle::eIdentity;
        create_image_view_info.components.g = vk::ComponentSwizzle::eIdentity;
        create_image_view_info.components.b = vk::ComponentSwizzle::eIdentity;
        create_image_view_info.components.a = vk::ComponentSwizzle::eIdentity;
        create_image_view_info.subresourceRange.aspectMask =
            vk::ImageAspectFlagBits::eColor;
        create_image_view_info.subresourceRange.baseMipLevel   = 0;
        create_image_view_info.subresourceRange.levelCount     = 1;
        create_image_view_info.subresourceRange.baseArrayLayer = 0;
        create_image_view_info.subresourceRange.layerCount     = 1;

        m_view = LOGICAL_DEVICE_INSTANCE.createImageViewUnique(
            create_image_view_info);
    }

    setupDepth(extent);
}

void
SwapChainFrame::addFrameBuffer(std::string_view key,
                               const vk::RenderPass& renderpass,
                               const vk::Extent2D& extent)
{
    std::vector<vk::ImageView> attachments = {m_view.get(),
                                              m_depth_image.view()};

    vk::FramebufferCreateInfo framebufferInfo;
    framebufferInfo.flags           = vk::FramebufferCreateFlags();
    framebufferInfo.renderPass      = renderpass;
    framebufferInfo.attachmentCount = attachments.size();
    framebufferInfo.pAttachments    = attachments.data();
    framebufferInfo.width           = extent.width;
    framebufferInfo.height          = extent.height;
    framebufferInfo.layers          = 1;

    m_framebuffers[key.data()] =
        LOGICAL_DEVICE_INSTANCE.createFramebufferUnique(framebufferInfo);
}

void
SwapChainFrame::setupCommandBuffer()
{
    m_command_buffer.create();
}

void
SwapChainFrame::setupSynchronization()
{
    m_sync_control.create();
}

void
SwapChainFrame::waitForFence()
{
    LOGICAL_DEVICE_INSTANCE.waitForFences(1, &(m_sync_control.inFlightFence()),
                                          VK_TRUE, UINT64_MAX);

    LOGICAL_DEVICE_INSTANCE.resetFences(1, &(m_sync_control.inFlightFence()));
}

void
SwapChainFrame::submitCommandBuffer()
{
    vk::SubmitInfo submitInfo = {};

    vk::PipelineStageFlags waitStages[] = {
        vk::PipelineStageFlagBits::eColorAttachmentOutput};

    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores    = m_sync_control.waitSemaphores();
    submitInfo.pWaitDstStageMask  = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = &(m_command_buffer.commandBuffer());

    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores    = m_sync_control.signalSemaphores();

    DEVICE_INSTANCE.getQueue("graphics")
        .submit(submitInfo, m_sync_control.inFlightFence());
}

}; // namespace kusengine::render
