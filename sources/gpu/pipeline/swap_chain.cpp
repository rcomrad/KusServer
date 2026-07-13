#include "swap_chain.hpp"

#include "kernel/framework/logger/include_me.hpp"

#include <algorithm>

#include "gpu/logic/device.hpp"
#include "gpu/window/surface.hpp"
#include "gpu/window/surface_characteristics.hpp"

gpu::pipeline::SwapChain::SwapChain(
    logic::Device& a_logic_device,
    window::Surface& a_serface,
    const window::SurfaceCharacteristics& a_characteristic)
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

gpu::pipeline::SwapChain::~SwapChain()
{
    m_logic_device.destroySwapchainKHR(*static_cast<vk::SwapchainKHR*>(this));
}

vk::SwapchainKHR
gpu::pipeline::SwapChain::create(
    logic::Device& a_logic_device,
    window::Surface& a_serface,
    const window::SurfaceCharacteristics& a_characteristic)
{
    SCOPED_TRACE_INIT("swap chain");

    std::vector<uint32_t> m_family_indexes{a_family_index};

    vk::SwapchainCreateInfoKHR info;
    info.setClipped(VK_TRUE)
        .setSurface(a_serface)
        .setMinImageCount(a_characteristic.image_num)
        .setImageFormat(a_characteristic.format)
        .setImageColorSpace(a_characteristic.color_space)
        .setImageExtent(a_capabilities.currentExtent)
        .setImageArrayLayers(1)
        .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment |
                       vk::ImageUsageFlagBits::eTransferDst)
        .setImageSharingMode(vk::SharingMode::eExclusive)
        .setQueueFamilyIndices(a_characteristic.family_index)
        .setPreTransform(a_capabilities.currentTransform)
        .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
        .setPresentMode(a_characteristic.present_mode)
        .setClipped(VK_TRUE);

    return a_logic_device.createSwapchainKHR(info);
}
