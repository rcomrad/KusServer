#include "device.hpp"

#include "engine/graphics/renderer/swap_chain.hpp"

namespace kusengine
{
bool
Device::create(const Instance& instance, const vk::SurfaceKHR& surface)
{
    if (!PhysicalDevice::create(instance, surface)) return false;

    if (!LogicalDevice::create(PhysicalDevice::device(),
                               PhysicalDevice::getQueueFamilyIndices()))
        return false;

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

Device&
Device::getInstance()
{
    static Device device;
    return device;
}

}; // namespace kusengine
