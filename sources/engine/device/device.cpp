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

const vk::Device&
Device::logicalDeviceConstRef() const
{
    return LogicalDevice::device();
}

const vk::PhysicalDevice&
Device::physicalDeviceConstRef() const
{
    return PhysicalDevice::device();
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

std::vector<SwapChainFrame>
Device::getSwapchainFrames(const vk::SwapchainKHR& swapchain,
                           const vk::Format& format) const
{
    std::vector<SwapChainFrame> frames;
    auto&& images = LogicalDevice::device().getSwapchainImagesKHR(swapchain);
    frames.resize(images.size());
    for (int i = 0; i < images.size(); ++i)
    {
        frames[i].createFrame(LogicalDevice::device(), images[i], format);
    }
    return frames;
}

}; // namespace kusengine
