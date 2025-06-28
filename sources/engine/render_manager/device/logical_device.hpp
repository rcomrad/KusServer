#ifndef LOGICAL_DEVICE_HPP
#define LOGICAL_DEVICE_HPP

#include <map>

#include "physical_device.hpp"

namespace kusengine
{
namespace render
{

struct QueueData
{
    uint32_t family_index;
    uint32_t queue_index;

    float priority;
};

class LogicalDevice
{
public:
    LogicalDevice() = default;

    void create(const vk::PhysicalDevice& physical_device,
                const QueueFamilyIndices& queue_family_indices);

    vk::Queue getQueue(const std::string& queue_name) const;

protected:
    const vk::Device& device() const;

private:
    vk::PhysicalDeviceFeatures setupDeviceFeatures();

    std::vector<vk::DeviceQueueCreateInfo> getQueuesInfo();

    void setupQueues(const QueueFamilyIndices& queue_family_indices);

    std::map<std::string, QueueData> m_queues;

    vk::UniqueDevice m_logical_device;
};
}; // namespace render
}; // namespace kusengine

#endif // LOGICAL_DEVICE_HPP
