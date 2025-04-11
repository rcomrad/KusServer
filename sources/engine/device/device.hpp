#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "logical_device.hpp"
#include "physical_device.hpp"

namespace kusengine
{
class Device final : public PhysicalDevice, public LogicalDevice
{
public:
    struct SwapChainSupportDetails
    {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    Device() = default;

    bool createDevice(Instance& instance, const vk::SurfaceKHR& surface);

    SwapChainSupportDetails getSurfaceSupportDetails(
        const vk::SurfaceKHR& surface) const;

    vk::UniqueSwapchainKHR createSwapChainUnique(
        const vk::SwapchainCreateInfoKHR& info) const;

    std::vector<vk::Image> getSwapchainImages(
        const vk::SwapchainKHR& swapchain) const;

private:
    // PhysicalDevice m_physical_device;

    // LogicalDevice m_logical_device;
};
}; // namespace kusengine

#endif // DEVICE_HPP
