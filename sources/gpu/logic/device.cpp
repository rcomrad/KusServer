#include "device.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

gpu::logic::Device::Device(hard::Device& a_device,
                           type::FamilyIndex a_family_index)
    : vk::Device(create(a_device, a_family_index, priority)),
      m_physical_device(a_device)
{
}

gpu::logic::Device::~Device()
{
    // m_physical_device.destroyDevice(*static_cast<vk::Device*>(this));
}

gpu::type::MemoryTypeIndex
gpu::logic::Device::getMemoryTypeIndex(
    type::MemoryTypeBits a_type_filter,
    vk::MemoryPropertyFlags a_properties) const
{
    return m_physical_device.getMemoryTypeIndex(a_type_filter, a_properties);
}

vk::Device
gpu::logic::Device::create(hard::Device& a_device,
                           type::FamilyIndex a_family_index,
                           float& a_priority)
{
    SCOPED_TRACE_INIT("logical device");

    a_priority = 1.0;

    const std::vector<const char*> extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME};

    std::vector<vk::DeviceQueueCreateInfo> queue_info;
    queue_info.emplace_back()
        .setQueueFamilyIndex(a_family_index)
        .setPQueuePriorities(&a_priority)
        .setQueueCount(1);

    vk::DeviceCreateInfo device_info;
    device_info.setQueueCreateInfos(queue_info)
        .setPEnabledExtensionNames(extensions);

    return a_device.createDevice(device_info);
}
