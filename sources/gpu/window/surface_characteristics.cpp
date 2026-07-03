#include "surface_characteristics.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

gpu::window::SurfaceCharacteristics::SurfaceCharacteristics(
    hard::Device& a_device,
    window::Surface& a_serface)
{
    SCOPED_TRACE_INIT("characteristics");

    family_index = findFamilyIndex(a_device, a_serface);

    auto temp_form = findFormat(a_device, a_serface);
    format         = temp_form.first;
    color_space    = temp_form.second;

    present_mode = findPresentMode(a_device, a_serface);
    capability   = a_device.getSurfaceCapabilitiesKHR(a_serface);
    image_num    = findCapabilityImageNum(capability);
}

uint32_t
gpu::window::SurfaceCharacteristics::findFamilyIndex(hard::Device& a_device,
                                                     window::Surface& a_serface)
{
    auto property = a_device.getQueueFamilyProperties();
    for (uint32_t i = 0; i < property.size(); ++i)
    {
        auto is_graphical =
            property[i].queueFlags & vk::QueueFlagBits::eCompute;
        bool is_surfaceble = a_device.getSurfaceSupportKHR(i, a_serface);

        if (is_graphical && is_surfaceble)
        {
            return i;
        }
    }

    THROW("No sutable queue in physical devices that surface can support");
}

std::pair<vk::Format, vk::ColorSpaceKHR>
gpu::window::SurfaceCharacteristics::findFormat(hard::Device& a_device,
                                                window::Surface& a_serface)
{
    auto format      = vk::Format(VK_FORMAT_B8G8R8A8_SRGB);
    auto color_space = vk::ColorSpaceKHR(VK_COLOR_SPACE_SRGB_NONLINEAR_KHR);

    auto all_formats = a_device.getSurfaceFormatsKHR(a_serface);
    for (auto& i : all_formats)
    {
        if (i.format == format && i.colorSpace == color_space)
        {
            return {format, color_space};
        }
    }

    THROW("No such m_surface format present in physical devices");
}

vk::PresentModeKHR
gpu::window::SurfaceCharacteristics::findPresentMode(hard::Device& a_device,
                                                     window::Surface& a_serface)
{
    auto target_mode   = vk::PresentModeKHR::eMailbox;
    auto fallback_mode = vk::PresentModeKHR::eFifo;

    auto modes = a_device.getSurfacePresentModesKHR(a_serface);
    if (std::ranges::contains(modes, target_mode))
    {
        LOG_INFO("Using mailbox present mode");
        return target_mode;
    }
    else if (std::ranges::contains(modes, fallback_mode))
    {
        LOG_WARNING("Using fifo present mode (fallback mode)");
        return fallback_mode;
    }

    THROW("No any present mode available");
}

uint32_t
gpu::window::SurfaceCharacteristics::findCapabilityImageNum(
    const vk::SurfaceCapabilitiesKHR& a_capabilities)
{
    uint32_t result = a_capabilities.minImageCount + 1;

    if (a_capabilities.maxImageCount > 0)
    {
        result = std::min(result, a_capabilities.maxImageCount);
    }

    LOG_INFO("Capability image num = %lu", result);

    return result;
}
