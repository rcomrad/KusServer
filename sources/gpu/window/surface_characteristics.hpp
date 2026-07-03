#pragma once

#include <vulkan/vulkan.hpp>

//****

#include "kernel/framework/variable/include_me.hpp"
#include <GLFW/glfw3.h>

#include "gpu/hardware/device.hpp"
#include "gpu/utils/typedef.hpp"

#include "surface.hpp"

namespace gpu::window
{

class SurfaceCharacteristics
{
public:
    SurfaceCharacteristics(hard::Device& a_device, window::Surface& a_serface);

    type::FamilyIndex family_index;
    vk::Format format;
    vk::ColorSpaceKHR color_space;
    vk::PresentModeKHR present_mode;
    vk::SurfaceCapabilitiesKHR capability;
    type::ImageNum image_num;

private:
    uint32_t findFamilyIndex(hard::Device& a_device,
                             window::Surface& a_serface);
    std::pair<vk::Format, vk::ColorSpaceKHR> findFormat(
        hard::Device& a_device,
        window::Surface& a_serface);
    vk::PresentModeKHR findPresentMode(hard::Device& a_device,
                                       window::Surface& a_serface);
    uint32_t findCapabilityImageNum(
        const vk::SurfaceCapabilitiesKHR& a_capabilities);
};

}; // namespace gpu::window
