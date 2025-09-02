#include "logical_device.hpp"

#include <iostream>

namespace kusengine
{
namespace render
{
vk::PhysicalDeviceFeatures
LogicalDevice::setupDeviceFeatures()
{
    vk::PhysicalDeviceFeatures features;
    return features;
}

const vk::Device&
LogicalDevice::device() const
{
    return m_logical_device.get();
}

std::vector<vk::DeviceQueueCreateInfo>
LogicalDevice::getQueuesInfo()
{
    std::vector<vk::DeviceQueueCreateInfo> res;

    vk::DeviceQueueCreateInfo graphics_queue_create_info =
        vk::DeviceQueueCreateInfo()
            .setPQueuePriorities(&(m_queues["graphics"].priority))
            .setQueueCount(1)
            .setQueueFamilyIndex(m_queues["graphics"].family_index);

    res.emplace_back(std::move(graphics_queue_create_info));

    if (m_queues["graphics"].family_index != m_queues["present"].family_index)
    {
        vk::DeviceQueueCreateInfo present_queue_create_info =
            vk::DeviceQueueCreateInfo()
                .setPQueuePriorities(&(m_queues["present"].priority))
                .setQueueCount(1)
                .setQueueFamilyIndex(m_queues["present"].family_index);
    }
    return res;
}

void
LogicalDevice::setupQueues(const QueueFamilyIndices& queue_family_indices)
{
    m_queues["graphics"] = {queue_family_indices.graphics_family.value(), 0,
                            1.f};
    m_queues["present"] = {queue_family_indices.present_family.value(), 0, 1.f};
}

vk::Queue
LogicalDevice::getQueue(const std::string& queue_name) const
{
    auto queue = *(m_queues.find(queue_name));

    return m_logical_device.get().getQueue(queue.second.family_index,
                                           queue.second.queue_index);
}

void
LogicalDevice::create(const vk::PhysicalDevice& physical_device,
                      const QueueFamilyIndices& queue_family_indices)
{
    std::vector<const char*> enabledLayers;
#ifdef _DEBUG

    enabledLayers.push_back("VK_LAYER_KHRONOS_validation");

#endif //_DEBUG

    // setup features
    vk::PhysicalDeviceFeatures device_features = setupDeviceFeatures();

    // setup queues

    setupQueues(queue_family_indices);

    auto queues_info = getQueuesInfo();

    std::vector<const char*> requested_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    vk::DeviceCreateInfo device_info =
        vk::DeviceCreateInfo()
            .setQueueCreateInfoCount(queues_info.size())
            .setQueueCreateInfos(queues_info)
            .setEnabledLayerCount(enabledLayers.size())
            .setPEnabledLayerNames(enabledLayers)
            .setPEnabledFeatures(&device_features)
            .setEnabledExtensionCount(requested_extensions.size())
            .setPEnabledExtensionNames(requested_extensions);

    m_logical_device = physical_device.createDeviceUnique(device_info);
}
}; // namespace render
}; // namespace kusengine
