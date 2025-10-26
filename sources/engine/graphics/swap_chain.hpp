#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/typedef.hpp"

#include "image_collection.hpp"
#include "render_pass.hpp"

namespace engine::graphics
{

class SwapChain
{
public:
    SwapChain(vk::Device a_logic_device,
              vk::SurfaceKHR a_serface,
              type::FamilyIndex a_family_index,
              vk::Format a_format,
              vk::ColorSpaceKHR a_color_space,
              vk::PresentModeKHR a_present_mode,
              vk::SurfaceCapabilitiesKHR a_capabilities,
              type::ImageNum a_image_num);

    inline vk::SwapchainKHR& get()
    {
        return *m_swapchain;
    }

private:
    vk::UniqueSwapchainKHR m_swapchain;
    std::vector<uint32_t> m_family_indexes;
};

} // namespace engine::graphics
