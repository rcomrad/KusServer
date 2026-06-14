#include "device.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

Device::Device(hard::Device& a_device, type::FamilyIndex a_family_index)
    : vk::Device(create(a_device, a_family_index, priority)),
      m_physical_device(a_device)
{
}

Device::~Device()
{
    // m_physical_device.destroyDevice(*static_cast<vk::Device*>(this));
}

vk::Device
Device::create(hard::Device& a_device,
               type::FamilyIndex a_family_index,
               float& a_priority)
{
    SCOPED_TRACE_INIT("logical device");

    a_priority = 1.0;

    const std::vector<const char*> extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME};

    static std::vector<vk::DeviceQueueCreateInfo> queue_info;
    queue_info.emplace_back()
        .setQueueFamilyIndex(a_family_index)
        .setPQueuePriorities(&a_priority)
        .setQueueCount(1);

    vk::DeviceCreateInfo device_info;
    device_info.setQueueCreateInfos(queue_info)
        .setPEnabledExtensionNames(extensions);

    return a_device.createDevice(device_info);
}

} // namespace engine::logic
