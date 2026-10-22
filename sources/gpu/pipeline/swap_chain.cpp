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
    : SwapchainKHRBase(create(a_logic_device, a_serface, a_characteristic),
                       a_logic_device)
{
}

void
gpu::pipeline::SwapchainKHRDeleter::operator()(logic::Device& a_device,
                                               vk::RenderPass& a_this) noexcept
{
    a_device.destroySwapchainKHR(a_this);
}

vk::SwapchainKHR
gpu::pipeline::SwapChain::create(
    logic::Device& a_logic_device,
    window::Surface& a_serface,
    const window::SurfaceCharacteristics& a_characteristic)
{
    SCOPED_TRACE_INIT("swap chain");

    std::vector<uint32_t> family_indexes{a_characteristic.family_index};

    vk::SwapchainCreateInfoKHR info;
    info.setClipped(VK_TRUE)
        .setSurface(a_serface)
        .setMinImageCount(a_characteristic.image_num)
        .setImageFormat(a_characteristic.format)
        .setImageColorSpace(a_characteristic.color_space)
        .setImageExtent(a_characteristic.capability.currentExtent)
        .setImageArrayLayers(1)
        .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment |
                       vk::ImageUsageFlagBits::eTransferDst)
        .setImageSharingMode(vk::SharingMode::eExclusive)
        .setQueueFamilyIndices(family_indexes)
        .setPreTransform(a_characteristic.capability.currentTransform)
        .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
        .setPresentMode(a_characteristic.present_mode)
        .setClipped(VK_TRUE);

    return a_logic_device.createSwapchainKHR(info);
}
