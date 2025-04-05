#ifndef SWAP_CHAIN_HPP
#define SWAP_CHAIN_HPP

#include "device.hpp"

namespace kusengine
{
class SwapChain final
{
public:
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    SwapChain() = default;

    SwapChain(Device* device_ptr, vk::Extent2D window_extent);

    ~SwapChain();

    void initSwapChain(Device* device_ptr, vk::Extent2D window_extent);

    SwapChain(const SwapChain&) = delete;

    SwapChain& operator=(const SwapChain&) = delete;

    vk::Framebuffer getFrameBuffer(int index);

    vk::RenderPass getRenderPass();

    size_t imageCount();

    vk::Extent2D getSwapChainExtent();

    uint32_t width();
    uint32_t height();

    float extentAspectRatio();
    vk::Format findDepthFormat();

    vk::Result acquireNextImage(uint32_t* image_index);
    vk::Result submitCommandBuffers(
        const std::vector<vk::CommandBuffer>& buffers,
        uint32_t* image_index);

private:
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();
    void createSyncObjects();

    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<vk::SurfaceFormatKHR>& availableFormats);
    vk::PresentModeKHR chooseSwapPresentMode(
        const std::vector<vk::PresentModeKHR>& available_modes);

    // VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&
    // capabilities);

    vk::Format m_swap_chain_image_format;
    vk::Extent2D m_swap_chain_extent;

    std::vector<vk::Framebuffer> m_swap_chain_framebuffers;
    vk::RenderPass m_render_pass;

    std::vector<vk::Image> m_swap_chain_images;
    std::vector<vk::ImageView> m_swap_chain_image_views;

    vk::Extent2D m_window_extent;
    vk::SwapchainKHR m_swap_chain;

    vk::Semaphore m_submit_semaphore;
    vk::Semaphore m_acquire_semaphore;
    vk::Fence m_img_available_fence;

    size_t currentFrame = 0;
    Device* m_device_ptr;
};
}; // namespace kusengine

#endif // SWAP_CHAIN_HPP
