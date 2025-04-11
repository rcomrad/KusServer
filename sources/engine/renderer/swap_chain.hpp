#ifndef SWAP_CHAIN_HPP
#define SWAP_CHAIN_HPP

#include <vulkan/vulkan.hpp>

#include <shared_mutex>
#include <vector>

#include "engine/device/device.hpp"

namespace kusengine
{
class Window;
class Instance;

class SwapChain
{
public:
    bool initSwapChain(const Device& device);

    const vk::SurfaceKHR& surface();

    void createSurface(Window& window, Instance& instance);

private:
    vk::SurfaceFormatKHR chooseSurfaceFormat(
        const std::vector<vk::SurfaceFormatKHR>& available_formats);

    vk::PresentModeKHR choosePresentMode(
        const std::vector<vk::PresentModeKHR>& available_present_modes);

    vk::Extent2D chooseExtent(uint32_t width,
                              uint32_t height,
                              vk::SurfaceCapabilitiesKHR capabilities);

    // Surface

    vk::UniqueSurfaceKHR m_surface;

    // Swapchain

    vk::UniqueSwapchainKHR m_swapchain;

    //
    std::vector<vk::UniqueImage> m_images;
    vk::Format m_format;
    vk::Extent2D m_extent;
};
}; // namespace kusengine

#endif // SWAP_CHAIN_HPP
