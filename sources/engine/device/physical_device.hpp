#ifndef PHYSICAL_DEVICE_HPP
#define PHYSICAL_DEVICE_HPP

#include <optional>

#include "engine/instance/instance.hpp"

namespace kusengine
{

struct QueueFamilyIndices
{
    bool isComplete();

    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;
};

class PhysicalDevice
{
public:
    bool createPhysicalDevice(const Instance& instance,
                              const vk::SurfaceKHR& surface);

    QueueFamilyIndices getQueueFamilyIndices() const;

protected:
    const vk::PhysicalDevice& device() const;

private:
    bool choosePhysicalDevice(const Instance& instance);

    QueueFamilyIndices findQueueFamilies(const vk::SurfaceKHR& surface) const;

    static bool isSuitable(const vk::PhysicalDevice& device);

    static bool checkDeviceExtensionSupport(
        const vk::PhysicalDevice& device,
        const std::vector<const char*>& requested_extensions);

    vk::PhysicalDevice m_physical_device;

    QueueFamilyIndices m_queue_family_indices;
};
}; // namespace kusengine
#endif // PHYSICAL_DEVICE_HPP
