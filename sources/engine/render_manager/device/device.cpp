#include "device.hpp"

#include "engine/render_manager/swap_chain/swap_chain.hpp"

namespace kusengine
{
namespace render
{
void
Device::create(const Instance& instance, const vk::SurfaceKHR& surface)
{
    PhysicalDevice::create(instance, surface);

    LogicalDevice::create(PhysicalDevice::device(),
                          PhysicalDevice::getQueueFamilyIndices());
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
}; // namespace render
}; // namespace kusengine
