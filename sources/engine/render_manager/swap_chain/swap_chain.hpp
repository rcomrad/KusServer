#ifndef SWAP_CHAIN_HPP
#define SWAP_CHAIN_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/render_manager/commands/command_pool.hpp"
#include "engine/render_manager/renderer/render_way.hpp"
#include "engine/render_manager/renderer/render_way_storage.hpp"
#include "engine/render_manager/renderer/render_way_type.hpp"
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

    // TODO: map framebuffers
    size_t createSwapChainFrames(const RenderWayStorage& render_way_storage);

    void createSurface(const kusengine::Window& window,
                       const Instance& instance) noexcept(false);
    // get

    const vk::SurfaceKHR& surface() const noexcept;

    vk::Extent2D extent() const noexcept;

    vk::Format format() const noexcept;

    const vk::SwapchainKHR& swapchain() const noexcept;
    //

    template <typename T_DrawableSystem>
    void drawFrame(uint32_t frame_index,
                   const RenderWay& render_way,
                   const T_DrawableSystem& dr_system);

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
    void recordCommandBuffer(SwapChainFrame& frame,
                             const RenderWay& render_way);
    // Surface

    vk::UniqueSurfaceKHR m_surface;

    // Swapchain

    vk::UniqueSwapchainKHR m_swapchain;

    // frames
    std::vector<SwapChainFrame> m_frames;

    vk::Format m_format;
    vk::Extent2D m_extent;
};

template <typename T_DrawableSystem>
void
SwapChain::drawFrame(uint32_t frame_index,
                     const RenderWay& render_way,
                     const T_DrawableSystem& dr_system)
{
    dr_system.update(m_frames[frame_index]);

    m_frames[frame_index].waitForFence();

    uint32_t image_index;

    auto acquire_res = LOGICAL_DEVICE_INSTANCE.acquireNextImageKHR(
        m_swapchain.get(), UINT64_MAX,
        m_frames[frame_index].synControl().imageAvailable(), nullptr);

    image_index = acquire_res.value;

    recordCommandBuffer(m_frames[frame_index], render_way);

    m_frames[frame_index].submitCommandBuffer();

    present(image_index, m_frames[frame_index].synControl().signalSemaphores());
}

}; // namespace render
}; // namespace kusengine

#endif // SWAP_CHAIN_HPP
