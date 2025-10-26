#include "swap_chain.hpp"

#include <algorithm>

#include "kernel/framework/logger/include_me.hpp"

namespace engine::graphics
{

SwapChain::SwapChain(vk::Device a_logic_device,
                     vk::SurfaceKHR a_serface,
                     type::FamilyIndex a_family_index,
                     vk::Format a_format,
                     vk::ColorSpaceKHR a_color_space,
                     vk::PresentModeKHR a_present_mode,
                     vk::SurfaceCapabilitiesKHR a_capabilities,
                     type::ImageNum a_image_num)
{
    SCOPED_TRACE_INIT("swap chain");

    m_family_indexes.emplace_back(a_family_index);

    vk::SwapchainCreateInfoKHR info;
    info.setClipped(VK_TRUE)
        .setSurface(a_serface)
        .setMinImageCount(a_image_num)
        .setImageFormat(a_format)
        .setImageColorSpace(a_color_space)
        .setImageExtent(a_capabilities.currentExtent)
        .setImageArrayLayers(1)
        .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment |
                       vk::ImageUsageFlagBits::eTransferDst)
        .setImageSharingMode(vk::SharingMode::eExclusive)
        .setQueueFamilyIndices(m_family_indexes)
        .setPreTransform(a_capabilities.currentTransform)
        .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
        .setPresentMode(a_present_mode)
        // .setOldSwapchain(VK_NULL_HANDLE)
        .setClipped(VK_TRUE);

    m_swapchain = a_logic_device.createSwapchainKHRUnique(info);
}

} // namespace engine::graphics
