#include "physical_device.hpp"

#include <iostream>
#include <set>
#include <string>

namespace kusengine
{
namespace render
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
PhysicalDevice::supportMailBox(const vk::PhysicalDevice& device,
                               const vk::SurfaceKHR& surface)
{
    for (vk::PresentModeKHR presentMode :
         device.getSurfacePresentModesKHR(surface))
    {
        if (presentMode == vk::PresentModeKHR::eMailbox)
        {
            return true;
        }
    }
    return false;
}

bool
PhysicalDevice::isSuitable(const vk::PhysicalDevice& device)
{
    static std::vector<const char*> requested_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    return checkDeviceExtensionSupport(device, requested_extensions);
}

void
PhysicalDevice::create(const Instance& instance, const vk::SurfaceKHR& surface)
{
    choosePhysicalDevice(instance, surface);

    m_queue_family_indices = findQueueFamilies(surface);
}

QueueFamilyIndices
PhysicalDevice::getQueueFamilyIndices() const
{
    return m_queue_family_indices;
}

void
PhysicalDevice::choosePhysicalDevice(const Instance& instance,
                                     const vk::SurfaceKHR& surface)
{
    auto available_devices = instance.getAvailablePhysicalDevices();

    for (vk::PhysicalDevice device : available_devices)
    {
        if (isSuitable(device) && supportMailBox(device, surface))
        {
            m_physical_device = device;
            return;
        }
    }
    for (vk::PhysicalDevice device : available_devices)
    {
        if (isSuitable(device))
        {
            m_physical_device = device;
            return;
        }
        
    }
    throw std::exception("Could not choose phsical device\n");
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

uint32_t
PhysicalDevice::findMemoryTypeIndex(
    uint32_t supported_memory_indices,
    vk::MemoryPropertyFlags requested_properties)
{
    vk::PhysicalDeviceMemoryProperties memoryProperties =
        m_physical_device.getMemoryProperties();

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        bool supported{static_cast<bool>(supported_memory_indices & (1 << i))};

        bool sufficient{(memoryProperties.memoryTypes[i].propertyFlags &
                         requested_properties) == requested_properties};

        if (supported && sufficient)
        {
            return i;
        }
    }

    return 0;
}
}; // namespace render
}; // namespace kusengine
