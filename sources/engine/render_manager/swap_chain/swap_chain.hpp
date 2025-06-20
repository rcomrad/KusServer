#ifndef SWAP_CHAIN_HPP
#define SWAP_CHAIN_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/render_manager/commands/command_pool.hpp"
#include "engine/render_manager/renderer/render_way.hpp"
#include "engine/render_manager/renderer/render_way_storage.hpp"
#include "engine/render_manager/renderer/render_way_types.hpp"
#include "engine/render_manager/renderer/renderer.hpp"

#include "swap_chain_frame.hpp"
#include "synchronization_control.hpp"

namespace kusengine
{
class Window;
namespace render
{

class Instance;
class Device;
class RenderPass;

class SwapChain
{
public:
    SwapChain() = default;
    //

    void create(uint32_t width, uint32_t height);

    // bool recreate(const Window& window, const Instance& instance);

    size_t createSwapChainFrames(const RenderWayStorage& render_way_storage);

    void createSurface(const kusengine::Window& window,
                       const Instance& instance) noexcept(false);
    // get

    const vk::SurfaceKHR& surface() const noexcept;

    vk::Extent2D extent() const noexcept;

    vk::Format format() const noexcept;

    const vk::SwapchainKHR& swapchain() const noexcept;
    //

    void drawFrame(uint32_t frame_index, const Renderer& renderer);

private:
    bool present(uint32_t index, const vk::Semaphore* wait_sems);

    vk::SurfaceFormatKHR chooseSurfaceFormat(
        const std::vector<vk::SurfaceFormatKHR>& available_formats) const;

    vk::PresentModeKHR choosePresentMode(
        const std::vector<vk::PresentModeKHR>& available_present_modes) const;

    vk::Extent2D chooseExtent(uint32_t width,
                              uint32_t height,
                              vk::SurfaceCapabilitiesKHR capabilities) const;

    uint32_t chooseImageCount(
        const vk::PresentModeKHR& present_mode,
        const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept;
    // Command buffer
    void recordCommandBuffer(const vk::PipelineLayout& pipelayout,
                             SwapChainFrame& frame,
                             const RenderPass& render_pass);
    // Surface

    vk::UniqueSurfaceKHR m_surface;

    // Swapchain

    vk::UniqueSwapchainKHR m_swapchain;

    // frames
    std::vector<SwapChainFrame> m_frames;

    vk::Format m_format;
    vk::Extent2D m_extent;
};
}; // namespace render
}; // namespace kusengine

#endif // SWAP_CHAIN_HPP
