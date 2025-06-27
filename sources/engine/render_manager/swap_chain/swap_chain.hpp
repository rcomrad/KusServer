#ifndef SWAP_CHAIN_HPP
#define SWAP_CHAIN_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/render_manager/commands/command_pool.hpp"
#include "engine/render_manager/descriptors/descriptor_manager.hpp"
#include "engine/render_manager/renderer/render_system.hpp"
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

    size_t createSwapChainFrames(const RenderSystem& render_system,
                                 const DescriptorManager& desc_manager);

    void createSurface(const kusengine::Window& window,
                       const Instance& instance) noexcept(false);

    template <typename MBDDType, typename UBOType>
    void updateFrame(int index,
                     const std::vector<MBDDType>& mbdd_vector,
                     const UBOType& ubo);
    // get

    SwapChainFrame& getFrame(int index) & noexcept;

    const vk::SurfaceKHR& surface() const& noexcept;

    const vk::Extent2D& extent() const& noexcept;

    const vk::Format& format() const& noexcept;

    const vk::SwapchainKHR& swapchain() const& noexcept;
    //

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

    // Surface

    vk::UniqueSurfaceKHR m_surface;

    // Swapchain

    vk::UniqueSwapchainKHR m_swapchain;

    // frames
    std::vector<SwapChainFrame> m_frames;

    vk::Format m_format;
    vk::Extent2D m_extent;
};

template <typename MBDDType, typename UBOType>
void
SwapChain::updateFrame(int index,
                       const std::vector<MBDDType>& mbdd_vector,
                       const UBOType& ubo)
{
    m_frames[index].updateMBDD(mbdd_vector);
    m_frames[index].updateUBO(ubo);
}

}; // namespace render
}; // namespace kusengine

#endif // SWAP_CHAIN_HPP
