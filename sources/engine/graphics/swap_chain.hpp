#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/typedef.hpp"
#include "engine/vk_converter.hpp"

#include "image_collection.hpp"
#include "render_pass.hpp"

namespace engine::graphics
{

class SwapChain : public vk::SwapchainKHR
{
public:
    SwapChain(logic::Device a_logic_device,
              vk::SurfaceKHR a_serface,
              type::FamilyIndex a_family_index,
              vk::Format a_format,
              vk::ColorSpaceKHR a_color_space,
              vk::PresentModeKHR a_present_mode,
              vk::SurfaceCapabilitiesKHR a_capabilities,
              type::ImageNum a_image_num);

    ~SwapChain();

    VK_CONVERTER(vk::SwapchainKHR);

private:
    logic::Device m_logic_device;
    // std::vector<uint32_t> m_family_indexes;

    // non=static for m_family_indexes
    static vk::SwapchainKHR create(logic::Device a_logic_device,
                                   vk::SurfaceKHR a_serface,
                                   type::FamilyIndex a_family_index,
                                   vk::Format a_format,
                                   vk::ColorSpaceKHR a_color_space,
                                   vk::PresentModeKHR a_present_mode,
                                   vk::SurfaceCapabilitiesKHR a_capabilities,
                                   type::ImageNum a_image_num);
};

} // namespace engine::graphics
