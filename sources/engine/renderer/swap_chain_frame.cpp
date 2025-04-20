#include "swap_chain_frame.hpp"

#include "swap_chain.hpp"
#include "synchronization_control.hpp"

namespace kusengine
{

const SynchronizationControl&
SwapChainFrame::synControl() const
{
    return m_sync_control;
}

const CommandBuffer&
SwapChainFrame::commandBuffer() const
{
    return m_command_buffer;
}

void
SwapChainFrame::createImage(const vk::Device& logical_device,
                            const vk::Image& image,
                            const vk::Format& format)
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

    m_view = logical_device.createImageViewUnique(create_image_view_info);
}

bool
SwapChainFrame::createFrameBuffer(const vk::Device& logical_device,
                                  const vk::RenderPass& renderpass,
                                  const vk::Extent2D& extent)
{
    std::vector<vk::ImageView> attachments = {m_view.get()};

    vk::FramebufferCreateInfo framebufferInfo;
    framebufferInfo.flags           = vk::FramebufferCreateFlags();
    framebufferInfo.renderPass      = renderpass;
    framebufferInfo.attachmentCount = attachments.size();
    framebufferInfo.pAttachments    = attachments.data();
    framebufferInfo.width           = extent.width;
    framebufferInfo.height          = extent.height;
    framebufferInfo.layers          = 1;

    try
    {
        m_framebuffer = logical_device.createFramebufferUnique(framebufferInfo);
    }
    catch (vk::SystemError err)
    {
        return false;
    }
    return true;
}

void
SwapChainFrame::createCommandBuffer(const CommandPool& command_pool)
{
    m_command_buffer.create(command_pool);
}

void
SwapChainFrame::createSynchronization(const Device& device)
{
    m_sync_control.create(device);
}

void
SwapChainFrame::waitForFence(const vk::Device& logical_device)
{
    logical_device.waitForFences(1, &(m_sync_control.inFlightFence()), VK_TRUE,
                                 UINT64_MAX);

    logical_device.resetFences(1, &(m_sync_control.inFlightFence()));
}

// void
// SwapChainFrame::recordCommandBuffer(const RenderPass& render_pass,
//                                     const SwapChain& swap_chain)
// {

//     const vk::CommandBuffer& command_buffer_ref =
//         m_command_buffer.commandBuffer();

//     command_buffer_ref.reset();

//     command_buffer_ref.reset();

//     vk::CommandBufferBeginInfo beginInfo = {};

//     command_buffer_ref.begin(beginInfo);

//     vk::RenderPassBeginInfo renderPassInfo = {};
//     renderPassInfo.renderPass              = render_pass.renderPass();
//     renderPassInfo.framebuffer             = m_frame_buffer.get();

//     renderPassInfo.renderArea.offset.x = 0;
//     renderPassInfo.renderArea.offset.y = 0;
//     renderPassInfo.renderArea.extent   = swap_chain.extent();

//     vk::ClearValue clearColor = {
//         std::array<float, 4>{1.0f, 0.5f, 0.25f, 1.0f}
//     };

//     renderPassInfo.clearValueCount = 1;
//     renderPassInfo.pClearValues    = &clearColor;

//     command_buffer_ref.beginRenderPass(&renderPassInfo,
//                                        vk::SubpassContents::eInline);

//     command_buffer_ref.bindPipeline(vk::PipelineBindPoint::eGraphics,
//                                     render_pass.graphicsPipeline().pipeline());

//     command_buffer_ref.draw(3, 1, 0, 0);

//     command_buffer_ref.endRenderPass();

//     command_buffer_ref.end();
// }

const vk::Framebuffer&
SwapChainFrame::framebuffer() const
{
    return m_framebuffer.get();
}

void
SwapChainFrame::submitCommandBuffer(const Device& device)
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

    device.getQueue("graphics")
        .submit(submitInfo, m_sync_control.inFlightFence());
}
}; // namespace kusengine
