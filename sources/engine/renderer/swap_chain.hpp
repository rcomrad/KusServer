#ifndef SWAP_CHAIN_HPP
#define SWAP_CHAIN_HPP

#include <vulkan/vulkan.hpp>

#include <shared_mutex>
#include <vector>

#include "engine/commands/command_pool.hpp"
#include "engine/device/device.hpp"
#include "engine/model/mesh_storage.hpp"
#include "engine/scene/scene.hpp"

#include "swap_chain_frame.hpp"
#include "synchronization_control.hpp"

namespace kusengine
{
class Window;
class Instance;
class Device;
class RenderPass;

class SwapChain
{
public:
    SwapChain(const RenderPass& render_pass);

    bool create(float width, float height);
    bool recreate(const Window& window, const Instance& instance);

    size_t createSwapChainFrames(const DescriptorManager& desc_manager);

    bool createSurface(const Window& window, const Instance& instance);
    // get

    const vk::SurfaceKHR& surface() const;

    vk::Extent2D extent() const;

    vk::Format format() const;

    const vk::SwapchainKHR& swapchain() const;
    //

    void drawFrame(uint32_t frame_index,
                   const Scene& scene,
                   const vk::PipelineLayout& pipelayout);

private:
    bool present(uint32_t index, const vk::Semaphore* wait_sems);

    vk::SurfaceFormatKHR chooseSurfaceFormat(
        const std::vector<vk::SurfaceFormatKHR>& available_formats);

    vk::PresentModeKHR choosePresentMode(
        const std::vector<vk::PresentModeKHR>& available_present_modes);

    vk::Extent2D chooseExtent(uint32_t width,
                              uint32_t height,
                              vk::SurfaceCapabilitiesKHR capabilities);

    uint32_t chooseImageCount(const vk::PresentModeKHR& present_mode,
                              const vk::SurfaceCapabilitiesKHR& capabilities);

    // Surface

    vk::UniqueSurfaceKHR m_surface;

    // Swapchain

    vk::UniqueSwapchainKHR m_swapchain;

    // frames
    std::vector<SwapChainFrame> m_frames;

    vk::Format m_format;
    vk::Extent2D m_extent;

    // Command buffer
    void recordCommandBuffer(const vk::PipelineLayout& pipelayout,
                             const Scene& scene,
                             const SwapChainFrame& frame);

    //  Refs
    const RenderPass& render_pass_ref;
};
}; // namespace kusengine

#endif // SWAP_CHAIN_HPP
