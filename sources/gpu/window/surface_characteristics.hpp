#pragma once

#include <vulkan/vulkan.hpp>

//****

#include <GLFW/glfw3.h>

#include "gpu/utils/typedef.hpp"

namespace gpu
{

namespace hard
{
class Device;
}

namespace window
{

class Surface;

class SurfaceCharacteristics
{
public:
    SurfaceCharacteristics(hard::Device& a_device, Surface& a_serface);

    type::FamilyIndex family_index;
    vk::Format format;
    vk::ColorSpaceKHR color_space;
    vk::PresentModeKHR present_mode;
    vk::SurfaceCapabilitiesKHR capability;
    type::ImageNum image_num;

private:
    uint32_t findFamilyIndex(hard::Device& a_device, Surface& a_serface);
    std::pair<vk::Format, vk::ColorSpaceKHR> findFormat(hard::Device& a_device,
                                                        Surface& a_serface);
    vk::PresentModeKHR findPresentMode(hard::Device& a_device,
                                       Surface& a_serface);
    uint32_t findCapabilityImageNum(
        const vk::SurfaceCapabilitiesKHR& a_capabilities);
};

} // namespace window

}; // namespace gpu
