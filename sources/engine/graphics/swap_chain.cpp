#include "swap_chain.hpp"

#include <algorithm>

#include "kernel/framework/logger/include_me.hpp"

namespace engine::graphics
{

SwapChain::SwapChain(logic::Device a_logic_device,
                     vk::SurfaceKHR a_serface,
                     type::FamilyIndex a_family_index,
                     vk::Format a_format,
                     vk::ColorSpaceKHR a_color_space,
                     vk::PresentModeKHR a_present_mode,
                     vk::SurfaceCapabilitiesKHR a_capabilities,
                     type::ImageNum a_image_num)
    : vk::SwapchainKHR(create(a_logic_device,
                              a_serface,
                              a_family_index,
                              a_format,
                              a_color_space,
                              a_present_mode,
                              a_capabilities,
                              a_image_num)),
      m_logic_device(a_logic_device)
{
}

SwapChain::~SwapChain()
{
    m_logic_device.destroySwapchainKHR(*static_cast<vk::SwapchainKHR*>(this));
}

vk::SwapchainKHR
SwapChain::create(logic::Device a_logic_device,
                  vk::SurfaceKHR a_serface,
                  type::FamilyIndex a_family_index,
                  vk::Format a_format,
                  vk::ColorSpaceKHR a_color_space,
                  vk::PresentModeKHR a_present_mode,
                  vk::SurfaceCapabilitiesKHR a_capabilities,
                  type::ImageNum a_image_num)
{
    SCOPED_TRACE_INIT("swap chain");

    std::vector<uint32_t> m_family_indexes{a_family_index};

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
        .setClipped(VK_TRUE);

    return a_logic_device.createSwapchainKHR(info);
}

} // namespace engine::graphics
