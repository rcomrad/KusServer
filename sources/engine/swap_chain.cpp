#include "swap_chain.hpp"

#include <array>

namespace kusengine
{
void
SwapChain::initSwapChain(Device* device_ptr, VkExtent2D extent)
{
    m_device_ptr    = device_ptr;
    m_window_extent = extent;
    createSwapChain();

    createImageViews();

    createRenderPass();

    createFramebuffers();

    createSyncObjects();
}

VkExtent2D
SwapChain::getSwapChainExtent()
{
    return m_swap_chain_extent;
}

VkFramebuffer
SwapChain::getFrameBuffer(int index)
{
    return m_swap_chain_framebuffers[index];
}

uint32_t
SwapChain::width()
{
    return m_swap_chain_extent.width;
}
uint32_t
SwapChain::height()
{
    return m_swap_chain_extent.height;
}

SwapChain::~SwapChain()
{
    for (auto imageView : m_swap_chain_image_views)
    {
        vkDestroyImageView(m_device_ptr->device(), imageView, nullptr);
    }
    m_swap_chain_image_views.clear();

    if (m_swap_chain != nullptr)
    {
        vkDestroySwapchainKHR(m_device_ptr->device(), m_swap_chain, nullptr);
        m_swap_chain = nullptr;
    }

    for (auto framebuffer : m_swap_chain_framebuffers)
    {
        vkDestroyFramebuffer(m_device_ptr->device(), framebuffer, nullptr);
    }

    vkDestroyRenderPass(m_device_ptr->device(), m_render_pass, nullptr);

    // cleanup synchronization objects

    vkDestroySemaphore(m_device_ptr->device(), m_submit_semaphore, nullptr);
    vkDestroySemaphore(m_device_ptr->device(), m_acuire_semaphore, nullptr);
    vkDestroyFence(m_device_ptr->device(), m_img_available_fence, nullptr);
}

void
SwapChain::acquireNextImage(uint32_t* image_index)
{
    vkWaitForFences(m_device_ptr->device(), 1, &m_img_available_fence, VK_TRUE,
                    UINT64_MAX);

    vkResetFences(m_device_ptr->device(), 1, &m_img_available_fence);

    vkAcquireNextImageKHR(m_device_ptr->device(), m_swap_chain, UINT64_MAX,
                          m_acuire_semaphore, 0, image_index);
}

void
SwapChain::submitCommandBuffers(const std::vector<VkCommandBuffer>& buffers,
                                uint32_t* image_index)
{
    VkSubmitInfo submit_info       = {};
    submit_info.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = static_cast<uint32_t>(buffers.size());

    VkPipelineStageFlags waitStage =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    submit_info.pCommandBuffers      = buffers.data();
    submit_info.pWaitDstStageMask    = &waitStage;
    submit_info.pSignalSemaphores    = &m_submit_semaphore;
    submit_info.signalSemaphoreCount = 1;
    submit_info.pWaitSemaphores      = &m_acuire_semaphore;
    submit_info.waitSemaphoreCount   = 1;
    vkQueueSubmit(m_device_ptr->graphicsQueue(), 1, &submit_info,
                  m_img_available_fence);

    VkPresentInfoKHR presentInfo   = {};
    presentInfo.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pSwapchains        = &m_swap_chain;
    presentInfo.swapchainCount     = 1;
    presentInfo.pImageIndices      = image_index;
    presentInfo.pWaitSemaphores    = &m_submit_semaphore;
    presentInfo.waitSemaphoreCount = 1;
    vkQueuePresentKHR(m_device_ptr->graphicsQueue(), &presentInfo);
}

VkRenderPass
SwapChain::getRenderPass()
{
    return m_render_pass;
}

size_t
SwapChain::imageCount()
{
    return m_swap_chain_images.size();
}

VkSurfaceFormatKHR
SwapChain::chooseSwapSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    for (const auto& availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

void
SwapChain::createSwapChain()
{
    auto swap_chain_support = m_device_ptr->getSwapChainSupport();
    VkSurfaceFormatKHR surface_format =
        chooseSwapSurfaceFormat(swap_chain_support.m_formats);

    uint32_t image_count = 0;

    image_count = swap_chain_support.m_capabilities.minImageCount + 1;

    image_count = image_count > swap_chain_support.m_capabilities.minImageCount
                      ? image_count - 1
                      : image_count;

    VkSwapchainCreateInfoKHR swapchain_info = {};
    swapchain_info.sType          = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_info.imageUsage     = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_info.surface        = m_device_ptr->surface();

    swapchain_info.imageFormat = surface_format.format;

    swapchain_info.preTransform =
        swap_chain_support.m_capabilities.currentTransform;
    swapchain_info.imageExtent =
        swap_chain_support.m_capabilities.currentExtent;
    swapchain_info.minImageCount    = image_count;
    swapchain_info.imageArrayLayers = 1;

    VkImageCreateInfo image_info{};
    image_info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.pNext         = nullptr;
    image_info.flags         = 0;
    image_info.imageType     = VK_IMAGE_TYPE_2D;
    image_info.format        = VK_FORMAT_R8G8B8A8_SRGB;
    image_info.extent.width  = swapchain_info.imageExtent.width;
    image_info.extent.height = swapchain_info.imageExtent.height;
    image_info.extent.depth  = 1;
    image_info.mipLevels     = 1;
    image_info.arrayLayers   = 1;
    image_info.samples       = VK_SAMPLE_COUNT_1_BIT;
    image_info.tiling        = VK_IMAGE_TILING_OPTIMAL;
    image_info.usage =
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT |
        VK_IMAGE_USAGE_SAMPLED_BIT; // Add sampled bit if you want to sample
                                    // from the image in a shader
    image_info.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    image_info.queueFamilyIndexCount = 0;
    image_info.pQueueFamilyIndices   = nullptr;
    image_info.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;

    m_swap_chain_images.resize(1);

    vkCreateImage(m_device_ptr->device(), &image_info, 0,
                  m_swap_chain_images.data());

    vkCreateSwapchainKHR(m_device_ptr->device(), &swapchain_info, 0,
                         &m_swap_chain);

    uint32_t swapchain_image_count;
    vkGetSwapchainImagesKHR(m_device_ptr->device(), m_swap_chain,
                            &swapchain_image_count, nullptr);
    m_swap_chain_images.resize(swapchain_image_count);
    vkGetSwapchainImagesKHR(m_device_ptr->device(), m_swap_chain,
                            &swapchain_image_count, m_swap_chain_images.data());

    m_swap_chain_image_format = surface_format.format;
    m_swap_chain_extent       = swap_chain_support.m_capabilities.currentExtent;
}

void
SwapChain::createImageViews()
{
    m_swap_chain_image_views.resize(imageCount());

    for (size_t i = 0; i < imageCount(); i++)
    {
        VkImageViewCreateInfo view_info{};
        view_info.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        view_info.image    = m_swap_chain_images[i];
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.format   = m_swap_chain_image_format;
        view_info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        view_info.subresourceRange.baseMipLevel   = 0;
        view_info.subresourceRange.levelCount     = 1;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount     = 1;

        vkCreateImageView(m_device_ptr->device(), &view_info, nullptr,
                          &m_swap_chain_image_views[i]);
    }
}

void
SwapChain::createRenderPass()
{
    auto swap_chain_support = m_device_ptr->getSwapChainSupport();
    VkSurfaceFormatKHR surface_format =
        chooseSwapSurfaceFormat(swap_chain_support.m_formats);

    VkAttachmentDescription attachment = {};
    attachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    attachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    attachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
    attachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
    attachment.format                  = surface_format.format;

    VkAttachmentReference color_attachmnet_ref = {};
    color_attachmnet_ref.attachment            = 0;
    color_attachmnet_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass_description = {};
    subpass_description.colorAttachmentCount = 1;
    subpass_description.pColorAttachments    = &color_attachmnet_ref;

    VkAttachmentDescription attachments[] = {attachment};
    uint32_t attachments_size             = 1;

    VkRenderPassCreateInfo renderpass_info = {};
    renderpass_info.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderpass_info.attachmentCount = attachments_size;
    renderpass_info.pAttachments    = attachments;
    renderpass_info.subpassCount    = 1;
    renderpass_info.pSubpasses      = &subpass_description;
    vkCreateRenderPass(m_device_ptr->device(), &renderpass_info, 0,
                       &m_render_pass);
}

void
SwapChain::createFramebuffers()
{
    m_swap_chain_framebuffers.resize(imageCount());
    for (size_t i = 0; i < imageCount(); i++)
    {
        std::array<VkImageView, 1> attachments = {m_swap_chain_image_views[i]};

        VkExtent2D swapChainExtent              = m_swap_chain_extent;
        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType      = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = m_render_pass;
        framebufferInfo.attachmentCount =
            static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width        = swapChainExtent.width;
        framebufferInfo.height       = swapChainExtent.height;
        framebufferInfo.layers       = 1;

        vkCreateFramebuffer(m_device_ptr->device(), &framebufferInfo, nullptr,
                            &m_swap_chain_framebuffers[i]);
    }
}

void
SwapChain::createSyncObjects()
{
    VkSemaphoreCreateInfo semaphore_info = {};
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    vkCreateSemaphore(m_device_ptr->device(), &semaphore_info, 0,
                      &m_acuire_semaphore);

    vkCreateSemaphore(m_device_ptr->device(), &semaphore_info, 0,
                      &m_submit_semaphore);

    VkFenceCreateInfo fence_info = {};
    fence_info.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

    vkCreateFence(m_device_ptr->device(), &fence_info, 0,
                  &m_img_available_fence);
}

}; // namespace kusengine
