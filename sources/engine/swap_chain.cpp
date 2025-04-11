#include "swap_chain.hpp"

#include <array>
#include <iostream>

namespace kusengine
{

OLDSwapChain::~OLDSwapChain()
{
    for (int i = 0; i < m_swap_chain_framebuffers.size(); ++i)
    {
        m_device_ptr->device().destroyFramebuffer(m_swap_chain_framebuffers[i]);
    }
    m_device_ptr->device().destroySwapchainKHR(m_swap_chain);
    m_device_ptr->device().destroyRenderPass(m_render_pass);
    // for (int i = 0; i < m_swap_chain_images.size(); ++i)
    // {
    //     m_device_ptr->device().destroyImage(m_swap_chain_images[i]);
    // }
    for (int i = 0; i < m_swap_chain_image_views.size(); ++i)
    {
        m_device_ptr->device().destroyImageView(m_swap_chain_image_views[i]);
    }

    m_device_ptr->device().destroySemaphore(m_submit_semaphore);
    m_device_ptr->device().destroySemaphore(m_acquire_semaphore);
    m_device_ptr->device().destroyFence(m_img_available_fence);
    m_device_ptr = nullptr;
    delete m_device_ptr;
}

void
OLDSwapChain::initSwapChain(Device* device_ptr, vk::Extent2D extent)
{
    m_device_ptr = device_ptr;

    m_window_extent = extent;

    createSwapChain();

    createImageViews();

    createRenderPass();

    createFramebuffers();

    createSyncObjects();
}

vk::Extent2D
OLDSwapChain::getSwapChainExtent()
{
    return m_swap_chain_extent;
}

vk::Framebuffer
OLDSwapChain::getFrameBuffer(int index)
{
    return m_swap_chain_framebuffers[index];
}

uint32_t
OLDSwapChain::width()
{
    return m_swap_chain_extent.width;
}
uint32_t
OLDSwapChain::height()
{
    return m_swap_chain_extent.height;
}

vk::Result
OLDSwapChain::acquireNextImage(uint32_t* image_index)
{
    auto waitResult = m_device_ptr->device().waitForFences(
        1, &m_img_available_fence,
        vk::True, // waitAll
        std::numeric_limits<uint64_t>::max());

    m_device_ptr->device().resetFences(1, &m_img_available_fence);

    try
    {
        *image_index =
            m_device_ptr->device()
                .acquireNextImageKHR(m_swap_chain,
                                     std::numeric_limits<uint64_t>::max(),
                                     m_acquire_semaphore, nullptr)
                .value;
    }
    catch (vk::OutOfDateKHRError&)
    {
        *image_index = 0;
        return vk::Result::eErrorOutOfDateKHR;
    }
}

vk::Result
OLDSwapChain::submitCommandBuffers(const std::vector<vk::CommandBuffer>& buffers,
                                uint32_t* image_index)
{
    vk::PipelineStageFlags wait_stage =
        vk::PipelineStageFlagBits::eColorAttachmentOutput;

    auto submit_info = vk::SubmitInfo()
                           .setCommandBufferCount(buffers.size())
                           .setPCommandBuffers(buffers.data())
                           .setWaitDstStageMask(wait_stage)
                           .setWaitSemaphoreCount(1)
                           .setPWaitSemaphores(&m_acquire_semaphore)
                           .setSignalSemaphoreCount(1)
                           .setPSignalSemaphores(&m_submit_semaphore);

    // Submit to graphics queue

    m_device_ptr->graphicsQueue().submit(1, &submit_info,
                                         m_img_available_fence);

    // Prepare present info
    auto presentInfo = vk::PresentInfoKHR()
                           .setSwapchainCount(1)
                           .setPSwapchains(&m_swap_chain)
                           .setPImageIndices(image_index)
                           .setWaitSemaphoreCount(1)
                           .setPWaitSemaphores(&m_submit_semaphore);

    // Present to queue
    try
    {
        auto presentResult =
            m_device_ptr->graphicsQueue().presentKHR(presentInfo);

        // Handle suboptimal/out-of-date as non-fatal errors
        if (presentResult == vk::Result::eSuboptimalKHR ||
            presentResult == vk::Result::eErrorOutOfDateKHR)
        {
            return presentResult;
        }
        else if (presentResult != vk::Result::eSuccess)
        {
            return presentResult;
        }
        return vk::Result::eSuccess;
    }
    catch (vk::OutOfDateKHRError&)
    {
        return vk::Result::eErrorOutOfDateKHR;
    }
}

vk::RenderPass
OLDSwapChain::getRenderPass()
{
    return m_render_pass;
}

size_t
OLDSwapChain::imageCount()
{
    return m_swap_chain_images.size();
}

vk::SurfaceFormatKHR
OLDSwapChain::chooseSwapSurfaceFormat(
    const std::vector<vk::SurfaceFormatKHR>& available_formats)
{
    constexpr vk::Format preferred_format = vk::Format::eB8G8R8A8Srgb;
    constexpr vk::ColorSpaceKHR preferred_color_space =
        vk::ColorSpaceKHR::eSrgbNonlinear;

    auto it =
        std::find_if(available_formats.begin(), available_formats.end(),
                     [](const vk::SurfaceFormatKHR& format)
                     {
                         return format.format == preferred_format &&
                                format.colorSpace == preferred_color_space;
                     });

    return (it != available_formats.end()) ? *it : available_formats[0];
}

vk::PresentModeKHR
OLDSwapChain::chooseSwapPresentMode(
    const std::vector<vk::PresentModeKHR>& available_modes)
{
    // Prefer mailbox (triple buffering) if available
    auto it = std::find(available_modes.begin(), available_modes.end(),
                        vk::PresentModeKHR::eMailbox);
    if (it != available_modes.end())
    {
        return *it;
    }

    // Otherwise fall back to FIFO (guaranteed to be available)
    return vk::PresentModeKHR::eFifo;
}

void
OLDSwapChain::createSwapChain()
{

    auto swap_chain_support = m_device_ptr->getSwapChainSupport();

    vk::SurfaceFormatKHR surface_format =
        chooseSwapSurfaceFormat(swap_chain_support.m_formats);

    uint32_t image_count =
        std::clamp(swap_chain_support.m_capabilities.minImageCount + 1,
                   swap_chain_support.m_capabilities.minImageCount,
                   swap_chain_support.m_capabilities.maxImageCount > 0
                       ? swap_chain_support.m_capabilities.maxImageCount
                       : std::numeric_limits<uint32_t>::max());

    vk::SwapchainCreateInfoKHR create_info(
        {}, // flags
        m_device_ptr->surface(), image_count, surface_format.format,
        surface_format.colorSpace,
        swap_chain_support.m_capabilities.currentExtent,
        1, // imageArrayLayers
        vk::ImageUsageFlagBits::eColorAttachment, vk::SharingMode::eExclusive,
        0,       // queueFamilyIndexCount
        nullptr, // pQueueFamilyIndices
        swap_chain_support.m_capabilities.currentTransform,
        vk::CompositeAlphaFlagBitsKHR::eOpaque,
        chooseSwapPresentMode(swap_chain_support.m_present_modes),
        true,   // clipped
        nullptr // oldSwapchain
    );

    m_swap_chain = m_device_ptr->device().createSwapchainKHR(create_info);

    auto swapchain_images =
        m_device_ptr->device().getSwapchainImagesKHR(m_swap_chain);

    m_swap_chain_images.resize(swapchain_images.size());
    for (int i = 0; i < swapchain_images.size(); ++i)
    {
        m_swap_chain_images[i] = swapchain_images[i];
    }

    m_swap_chain_image_format = surface_format.format;
    m_swap_chain_extent       = swap_chain_support.m_capabilities.currentExtent;
}

void
OLDSwapChain::createImageViews()
{
    m_swap_chain_image_views.resize(imageCount());

    for (size_t i = 0; i < imageCount(); i++)
    {
        vk::ImageViewCreateInfo view_info(
            {}, // flags
            m_swap_chain_images[i], vk::ImageViewType::e2D,
            m_swap_chain_image_format, {}, // components (default mapping)
            vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor,
                                      0, // baseMipLevel
                                      1, // levelCount
                                      0, // baseArrayLayer
                                      1  // layerCount
                                      ));

        m_swap_chain_image_views[i] =
            m_device_ptr->device().createImageView(view_info);
    }
}
void
OLDSwapChain::createRenderPass()
{
    auto swap_chain_support = m_device_ptr->getSwapChainSupport();
    auto surface_format = chooseSwapSurfaceFormat(swap_chain_support.m_formats);

    vk::AttachmentDescription color_attachment(
        {}, // flags
        surface_format.format, vk::SampleCountFlagBits::e1,
        vk::AttachmentLoadOp::eClear,     // loadOp
        vk::AttachmentStoreOp::eStore,    // storeOp
        vk::AttachmentLoadOp::eDontCare,  // stencilLoadOp
        vk::AttachmentStoreOp::eDontCare, // stencilStoreOp
        vk::ImageLayout::eUndefined,      // initialLayout
        vk::ImageLayout::ePresentSrcKHR   // finalLayout
    );

    vk::AttachmentReference color_attachment_ref(
        0, // attachment index
        vk::ImageLayout::eColorAttachmentOptimal);

    vk::SubpassDescription subpass({}, // flags
                                   vk::PipelineBindPoint::eGraphics,
                                   0,       // inputAttachmentCount
                                   nullptr, // pInputAttachments
                                   1,       // colorAttachmentCount
                                   &color_attachment_ref,
                                   nullptr, // pResolveAttachments
                                   nullptr, // pDepthStencilAttachment
                                   0,       // preserveAttachmentCount
                                   nullptr  // pPreserveAttachments
    );

    vk::RenderPassCreateInfo render_pass_info({}, // flags
                                              1, &color_attachment, 1, &subpass,
                                              0, nullptr // dependencies
    );

    m_render_pass = m_device_ptr->device().createRenderPass(render_pass_info);
}

void
OLDSwapChain::createFramebuffers()
{
    m_swap_chain_framebuffers.resize(imageCount());

    for (size_t i = 0; i < imageCount(); i++)
    {
        std::array<vk::ImageView, 1> attachments = {
            m_swap_chain_image_views[i]};

        vk::FramebufferCreateInfo framebuffer_info({}, // flags
                                                   m_render_pass, attachments,
                                                   m_swap_chain_extent.width,
                                                   m_swap_chain_extent.height,
                                                   1 // layers
        );

        m_swap_chain_framebuffers[i] =
            m_device_ptr->device().createFramebuffer(framebuffer_info);
    }
}

void
OLDSwapChain::createSyncObjects()
{
    vk::SemaphoreCreateInfo semaphore_info;
    m_acquire_semaphore =
        m_device_ptr->device().createSemaphore(semaphore_info);
    m_submit_semaphore = m_device_ptr->device().createSemaphore(semaphore_info);

    vk::FenceCreateInfo fence_info(
        vk::FenceCreateFlagBits::eSignaled // Initially signaled
    );
    m_img_available_fence = m_device_ptr->device().createFence(fence_info);
}

OLDSwapChain::OLDSwapChain(Device* device_ptr, vk::Extent2D window_extent)
{
    initSwapChain(device_ptr, window_extent);
}
}; // namespace kusengine
