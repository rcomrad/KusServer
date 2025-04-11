#include "physical_device.hpp"

#include <set>
#include <string>

namespace kusengine
{
bool
PhysicalDevice::checkDeviceExtensionSupport(
    const vk::PhysicalDevice& device,
    const std::vector<const char*>& requested_extensions)
{
    std::set<std::string> requiredExtensions(requested_extensions.begin(),
                                             requested_extensions.end());

    for (vk::ExtensionProperties& extension :
         device.enumerateDeviceExtensionProperties())
    {
        requiredExtensions.erase(extension.extensionName);
    }
    return requiredExtensions.empty();
}

bool
PhysicalDevice::isSuitable(const vk::PhysicalDevice& device)
{
    static std::vector<const char*> requested_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    return checkDeviceExtensionSupport(device, requested_extensions);
}

bool
PhysicalDevice::createPhysicalDevice(const Instance& instance,
                                     const vk::SurfaceKHR& surface)
{
    bool s = choosePhysicalDevice(instance);
    if (!s) return false;

    m_queue_family_indices = findQueueFamilies(surface);

    return true;
}

QueueFamilyIndices
PhysicalDevice::getQueueFamilyIndices() const
{
    return m_queue_family_indices;
}

bool
PhysicalDevice::choosePhysicalDevice(const Instance& instance)
{
    auto available_devices = instance.getAvailablePhysicalDevices();

    for (vk::PhysicalDevice device : available_devices)
    {
        if (isSuitable(device))
        {
            m_physical_device = device;
            return true;
        }
    }
    return false;
}

bool
QueueFamilyIndices::isComplete()
{
    return graphics_family.has_value() && present_family.has_value();
}

QueueFamilyIndices
PhysicalDevice::findQueueFamilies(const vk::SurfaceKHR& surface) const
{
    QueueFamilyIndices indices;

    std::vector<vk::QueueFamilyProperties> queueFamilies =
        m_physical_device.getQueueFamilyProperties();

    int i = 0;

    for (vk::QueueFamilyProperties queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
        {
            indices.graphics_family = i;
        }

        if (m_physical_device.getSurfaceSupportKHR(i, surface))
        {
            indices.present_family = i;
        }

        if (indices.isComplete())
        {
            break;
        }

        i++;
    }

    return indices;
}

const vk::PhysicalDevice&
PhysicalDevice::device() const
{
    return m_physical_device;
}
}; // namespace kusengine
