#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/utils/typedef.hpp"
#include "gpu/utils/vk_converter.hpp"
#include "gpu/window/surface.hpp"

#include "image_collection.hpp"
#include "render_pass.hpp"

namespace gpu::pipeline
{

class SwapChain : public vk::SwapchainKHR
{
public:
    SwapChain(logic::Device& a_logic_device,
              window::Surface& a_serface,
              type::FamilyIndex a_family_index,
              vk::Format a_format,
              vk::ColorSpaceKHR a_color_space,
              vk::PresentModeKHR a_present_mode,
              vk::SurfaceCapabilitiesKHR a_capabilities,
              type::ImageNum a_image_num);

    ~SwapChain();
    HOLY_TRINITY_NOCOPY(SwapChain);

    VK_CONVERTER(vk::SwapchainKHR);

private:
    logic::Device& m_logic_device;

    static vk::SwapchainKHR create(logic::Device& a_logic_device,
                                   window::Surface& a_serface,
                                   type::FamilyIndex a_family_index,
                                   vk::Format a_format,
                                   vk::ColorSpaceKHR a_color_space,
                                   vk::PresentModeKHR a_present_mode,
                                   vk::SurfaceCapabilitiesKHR a_capabilities,
                                   type::ImageNum a_image_num);
};

} // namespace gpu::pipeline
