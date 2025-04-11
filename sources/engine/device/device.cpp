#include "device.hpp"

namespace kusengine
{
bool
Device::createDevice(Instance& instance, const vk::SurfaceKHR& surface)
{
    bool success = createPhysicalDevice(instance, surface);

    if (!success) return false;

    success = createLogicalDevice(PhysicalDevice::device(),
                                  PhysicalDevice::getQueueFamilyIndices());

    if (!success) return false;

    return true;
}
Device::SwapChainSupportDetails
Device::getSurfaceSupportDetails(const vk::SurfaceKHR& surface) const
{
    return {
        PhysicalDevice::device().getSurfaceCapabilitiesKHR(surface),
        PhysicalDevice::device().getSurfaceFormatsKHR(surface),
        PhysicalDevice::device().getSurfacePresentModesKHR(surface),
    };
}

vk::UniqueSwapchainKHR
Device::createSwapChainUnique(const vk::SwapchainCreateInfoKHR& info) const
{
    return LogicalDevice::device().createSwapchainKHRUnique(info);
}

std::vector<vk::Image>
Device::getSwapchainImages(const vk::SwapchainKHR& swapchain) const
{
    return LogicalDevice::device().getSwapchainImagesKHR(swapchain);
}

}; // namespace kusengine
