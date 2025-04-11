#include "swap_chain.hpp"

#include "engine/instance/instance.hpp"
#include "engine/window/window.hpp"

namespace kusengine
{

void
SwapChain::createSurface(Window& window, Instance& instance)
{
    VkSurfaceKHR c_style_surface{};

    window.createWindowSurface(instance.get(), c_style_surface);

    m_surface.get() = c_style_surface;
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

bool
SwapChain::initSwapChain(const Device& device)
{
    auto support = device.getSurfaceSupportDetails(surface());

    vk::SurfaceFormatKHR format = chooseSurfaceFormat(support.formats);

    vk::PresentModeKHR presentMode = choosePresentMode(support.presentModes);

    // TODO: add width and heigth
    vk::Extent2D extent = chooseExtent(0, 0, support.capabilities);

    uint32_t image_count = std::min(support.capabilities.maxImageCount,
                                    support.capabilities.minImageCount + 1);

    vk::SwapchainCreateInfoKHR create_info = vk::SwapchainCreateInfoKHR(
        vk::SwapchainCreateFlagsKHR(), surface(), image_count, format.format,
        format.colorSpace, extent, 1, vk::ImageUsageFlagBits::eColorAttachment);

    QueueFamilyIndices indices = device.getQueueFamilyIndices();

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
    create_info.presentMode    = presentMode;
    create_info.clipped        = VK_TRUE;

    create_info.oldSwapchain = vk::SwapchainKHR(nullptr);

    try
    {
        m_swapchain =
            device.logicalDeviceConstRef().createSwapchainKHRUnique(
                create_info);
    }
    catch (vk::SystemError err)
    {
        return false;
    }

    m_frames = device.getSwapchainFrames(m_swapchain.get(), format.format);

    m_format = format.format;
    m_extent = extent;

    return true;
}

const vk::SurfaceKHR&
SwapChain::surface()
{
    return m_surface.get();
}
}; // namespace kusengine
