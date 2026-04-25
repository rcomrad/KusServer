#pragma once

#include <vulkan/vulkan.hpp>

//****

#include <GLFW/glfw3.h>

#include "engine/typedef.hpp"
#include "kernel/framework/variable/include_me.hpp"

namespace engine::window
{

class SurfaceCharacteristics
{
public:
    SurfaceCharacteristics(vk::PhysicalDevice& a_device,
                           vk::SurfaceKHR a_serface);

    type::FamilyIndex family_index;
    vk::Format format;
    vk::ColorSpaceKHR color_space;
    vk::PresentModeKHR present_mode;
    vk::SurfaceCapabilitiesKHR capability;
    type::ImageNum image_num;

private:
    uint32_t findFamilyIndex(vk::PhysicalDevice& a_device,
                             vk::SurfaceKHR a_serface);
    std::pair<vk::Format, vk::ColorSpaceKHR> findFormat(
        vk::PhysicalDevice& a_device,
        vk::SurfaceKHR a_serface);
    vk::PresentModeKHR findPresentMode(vk::PhysicalDevice& a_device,
                                       vk::SurfaceKHR a_serface);
    uint32_t findCapabilityImageNum(
        const vk::SurfaceCapabilitiesKHR& a_capabilities);
};

}; // namespace engine::window
