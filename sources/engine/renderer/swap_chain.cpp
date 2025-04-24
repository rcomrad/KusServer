#include "swap_chain.hpp"

#include <iostream>

#include "engine/device/device.hpp"
#include "engine/instance/instance.hpp"
#include "engine/window/window.hpp"
#include "render_pass.hpp"

namespace kusengine
{

SwapChain::SwapChain(const CommandPool& command_pool,
                     const RenderPass& render_pass)
    : command_pool_ref(command_pool),
      render_pass_ref(render_pass)
{
}

const vk::SurfaceKHR&
SwapChain::surface() const
{
    return m_surface.get();
}

vk::Extent2D
SwapChain::extent() const
{
    return m_extent;
}

vk::Format
SwapChain::format() const
{
    return m_format;
}

const vk::SwapchainKHR&
SwapChain::swapchain() const
{
    return m_swapchain.get();
}

bool
SwapChain::createSurface(const Window& window, const Instance& instance)
{
    VkSurfaceKHR c_style_surface{};

    if (!window.createWindowSurface(instance.get(), c_style_surface))
    {
        std::cerr << "Failed to create window surface";
        return false;
    }

    m_surface.get() = c_style_surface;

    return true;
}

vk::SurfaceFormatKHR
SwapChain::chooseSurfaceFormat(
    const std::vector<vk::SurfaceFormatKHR>& available_formats)
{
    for (vk::SurfaceFormatKHR format : available_formats)
    {
        if (format.format == vk::Format::eB8G8R8A8Unorm &&
            format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
        {
            return format;
        }
    }

    return available_formats[0];
}

vk::PresentModeKHR
SwapChain::choosePresentMode(
    const std::vector<vk::PresentModeKHR>& available_present_modes)
{
    for (vk::PresentModeKHR presentMode : available_present_modes)
    {
        // if (presentMode == vk::PresentModeKHR::eImmediate)
        // {
        //     return presentMode;
        // }
        if (presentMode == vk::PresentModeKHR::eMailbox)
        {
            return presentMode;
        }
    }

    return vk::PresentModeKHR::eFifo;
}

vk::Extent2D
SwapChain::chooseExtent(uint32_t width,
                        uint32_t height,
                        vk::SurfaceCapabilitiesKHR capabilities)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    else
    {
        vk::Extent2D extent = {width, height};

        extent.width =
            std::min(capabilities.maxImageExtent.width,
                     std::max(capabilities.minImageExtent.width, extent.width));

        extent.height = std::min(
            capabilities.maxImageExtent.height,
            std::max(capabilities.minImageExtent.height, extent.height));

        return extent;
    }
}

uint32_t
SwapChain::chooseImageCount(const vk::PresentModeKHR& present_mode,
                            const vk::SurfaceCapabilitiesKHR& capabilities)
{
    uint32_t res = 2;
    if (present_mode == vk::PresentModeKHR::eMailbox) res = 3;
    return std::min(capabilities.maxImageCount, res);
}

bool
SwapChain::recreate(const Window& window, const Instance& instance)
{
    createSurface(window, instance);
    if (!create(window.getExtent().width, window.getExtent().height))
        return false;
    createSwapChainFrames();
    return true;
}

bool
SwapChain::create(float width, float height)
{
    auto support = DEVICE.getSurfaceSupportDetails(surface());

    vk::SurfaceFormatKHR format = chooseSurfaceFormat(support.formats);

    vk::PresentModeKHR present_mode = choosePresentMode(support.presentModes);

    vk::Extent2D extent = chooseExtent(width, height, support.capabilities);

    uint32_t image_count = chooseImageCount(present_mode, support.capabilities);

    vk::SwapchainCreateInfoKHR create_info = vk::SwapchainCreateInfoKHR(
        vk::SwapchainCreateFlagsKHR(), surface(), image_count, format.format,
        format.colorSpace, extent, 1, vk::ImageUsageFlagBits::eColorAttachment);

    QueueFamilyIndices indices = DEVICE.getQueueFamilyIndices();

    uint32_t queue_family_indices[] = {indices.graphics_family.value(),
                                       indices.present_family.value()};

    if (indices.graphics_family != indices.present_family)
    {
        create_info.imageSharingMode      = vk::SharingMode::eConcurrent;
        create_info.queueFamilyIndexCount = 2;
        create_info.pQueueFamilyIndices   = queue_family_indices;
    }
    else
    {
        create_info.imageSharingMode = vk::SharingMode::eExclusive;
    }

    create_info.preTransform   = support.capabilities.currentTransform;
    create_info.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    create_info.presentMode    = present_mode;
    create_info.clipped        = VK_TRUE;

    create_info.oldSwapchain = vk::SwapchainKHR(nullptr);

    try
    {
        m_swapchain =
            LOGICAL_DEVICE.createSwapchainKHRUnique(
                create_info);
    }
    catch (vk::SystemError err)
    {
        return false;
    }

    m_format = format.format;
    m_extent = extent;

    return true;
}

void
SwapChain::createSwapChainFrames()
{
    auto images = LOGICAL_DEVICE.getSwapchainImagesKHR(
        m_swapchain.get());

    m_frames.resize(images.size());
    for (int i = 0; i < images.size(); ++i)
    {
        m_frames[i].createImage(images[i],
                                m_format);
        m_frames[i].createFrameBuffer(
                                      render_pass_ref.renderPass(), m_extent);
        m_frames[i].createCommandBuffer(command_pool_ref);
        m_frames[i].createSynchronization();
    }
}

bool
SwapChain::present(uint32_t index, const vk::Semaphore* wait_sems)
{
    vk::PresentInfoKHR presentInfo = {};
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores    = wait_sems;

    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains    = &m_swapchain.get();
    presentInfo.pImageIndices  = &index;

    vk::Result present;
    try
    {
        present = DEVICE.getQueue("present").presentKHR(presentInfo);
    }
    catch (vk::OutOfDateKHRError error)
    {
        present = vk::Result::eErrorOutOfDateKHR;
    }

    if (present == vk::Result::eErrorOutOfDateKHR ||
        present == vk::Result::eSuboptimalKHR)
    {
        // recreate();
        return false;
    }
    return true;
}

void
SwapChain::recordCommandBuffer(const CommandBuffer& command_buffer,
                               const vk::Framebuffer& framebuffer,
                               const Scene& scene)
{
    const vk::CommandBuffer& command_buffer_ref =
        command_buffer.commandBuffer();

    command_buffer_ref.reset();

    vk::CommandBufferBeginInfo beginInfo = {};

    command_buffer_ref.begin(beginInfo);

    vk::RenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.renderPass              = render_pass_ref.renderPass();
    renderPassInfo.framebuffer             = framebuffer;

    renderPassInfo.renderArea.offset.x = 0;
    renderPassInfo.renderArea.offset.y = 0;
    renderPassInfo.renderArea.extent   = extent();

    vk::ClearValue clearColor = {
        std::array<float, 4>{1.0f, 0.5f, 0.25f, 1.0f}
    };

    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues    = &clearColor;

    command_buffer_ref.beginRenderPass(&renderPassInfo,
                                       vk::SubpassContents::eInline);

    command_buffer_ref.bindPipeline(
        vk::PipelineBindPoint::eGraphics,
        render_pass_ref.graphicsPipeline().pipeline());

    scene.draw(command_buffer_ref);

    command_buffer_ref.endRenderPass();

    command_buffer_ref.end();
}

void
SwapChain::drawFrame(uint32_t frame_index, const Scene& scene)
{

    m_frames[frame_index].waitForFence();

    uint32_t image_index;

    auto acquire_res = LOGICAL_DEVICE.acquireNextImageKHR(
        m_swapchain.get(), UINT64_MAX,
        m_frames[frame_index].synControl().imageAvailable(), nullptr);

    image_index = acquire_res.value;

    const auto& command_buffer = m_frames[frame_index].commandBuffer();
    const auto& framebuffer    = m_frames[frame_index].framebuffer();

    recordCommandBuffer(command_buffer, framebuffer, scene);

    m_frames[frame_index].submitCommandBuffer();

    present(image_index, m_frames[frame_index].synControl().signalSemaphores());
}

}; // namespace kusengine
