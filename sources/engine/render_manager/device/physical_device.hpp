#ifndef PHYSICAL_DEVICE_HPP
#define PHYSICAL_DEVICE_HPP

#include <optional>

#include "engine/render_manager/instance/instance.hpp"

namespace kusengine
{
namespace render
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
    void create(const Instance& instance, const vk::SurfaceKHR& surface);

    QueueFamilyIndices getQueueFamilyIndices() const;

    uint32_t findMemoryTypeIndex(uint32_t supported_memory_indices,
                                 vk::MemoryPropertyFlags requested_properties);

protected:
    const vk::PhysicalDevice& device() const;

private:
    void choosePhysicalDevice(const Instance& instance,
                              const vk::SurfaceKHR& surface);

    QueueFamilyIndices findQueueFamilies(const vk::SurfaceKHR& surface) const;

    static bool isSuitable(const vk::PhysicalDevice& device);

    static bool checkDeviceExtensionSupport(
        const vk::PhysicalDevice& device,
        const std::vector<const char*>& requested_extensions);

    static bool supportMailBox(const vk::PhysicalDevice& device,
                               const vk::SurfaceKHR& surface);

    vk::PhysicalDevice m_physical_device;

    QueueFamilyIndices m_queue_family_indices;
};
}; // namespace render
}; // namespace kusengine
#endif // PHYSICAL_DEVICE_HPP
