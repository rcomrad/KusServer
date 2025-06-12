#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "logical_device.hpp"
#include "physical_device.hpp"

namespace kusengine
{
class SwapChain;

class Device final : public PhysicalDevice, public LogicalDevice
{
public:
    struct SwapChainSupportDetails
    {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    static Device& getInstance();

    bool create(const Instance& instance,
                const vk::SurfaceKHR& surface) override;

    const vk::Device& logicalDeviceConstRef() const;

    const vk::PhysicalDevice& physicalDeviceConstRef() const;

    SwapChainSupportDetails getSurfaceSupportDetails(
        const vk::SurfaceKHR& surface) const;

private:
    Device() = default;
};

#define DEVICE          Device::getInstance()
#define LOGICAL_DEVICE  Device::getInstance().logicalDeviceConstRef()
#define PHYSICAL_DEVICE Device::getInstance().physicalDeviceConstRef()

}; // namespace kusengine

#endif // DEVICE_HPP
