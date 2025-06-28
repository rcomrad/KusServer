#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "logical_device.hpp"
#include "physical_device.hpp"

namespace kusengine
{
namespace render
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

    void create(const Instance& instance, const vk::SurfaceKHR& surface);

    const vk::Device& logicalDeviceConstRef() const;

    const vk::PhysicalDevice& physicalDeviceConstRef() const;

    SwapChainSupportDetails getSurfaceSupportDetails(
        const vk::SurfaceKHR& surface) const;

private:
    Device() = default;
};

#define DEVICE_INSTANCE          Device::getInstance()
#define LOGICAL_DEVICE_INSTANCE  Device::getInstance().logicalDeviceConstRef()
#define PHYSICAL_DEVICE_INSTANCE Device::getInstance().physicalDeviceConstRef()

}; // namespace render
}; // namespace kusengine

#endif // DEVICE_HPP
