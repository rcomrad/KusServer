#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "engine/renderer/swap_chain_frame.hpp"

#include "logical_device.hpp"
#include "physical_device.hpp"

// #include "swap_chain.hpp"
#include "engine/renderer/render_pass.hpp"

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

    Device() = default;

    bool create(const Instance& instance,
                const vk::SurfaceKHR& surface) override;

    const vk::Device& logicalDeviceConstRef() const;

    const vk::PhysicalDevice& physicalDeviceConstRef() const;

    SwapChainSupportDetails getSurfaceSupportDetails(
        const vk::SurfaceKHR& surface) const;

private:
};
}; // namespace kusengine

#endif // DEVICE_HPP
