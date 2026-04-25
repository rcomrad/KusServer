#include "device.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

Device::Device(vk::PhysicalDevice& a_device, type::FamilyIndex a_family_index)
{
    SCOPED_TRACE_INIT("logical device");

    const std::vector<const char*> extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME};

    std::vector<vk::DeviceQueueCreateInfo> queue_info;
    queue_info.emplace_back()
        .setQueueFamilyIndex(a_family_index)
        .setPQueuePriorities(&priority)
        .setQueueCount(1);

    vk::DeviceCreateInfo device_info;
    device_info.setQueueCreateInfos(queue_info)
        .setPEnabledExtensionNames(extensions);

    m_device = a_device.createDeviceUnique(device_info);
}

vk::Device&
Device::get()
{
    return *m_device;
}

} // namespace engine::logic
