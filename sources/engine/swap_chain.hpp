#ifndef SWAP_CHAIN_HPP
#define SWAP_CHAIN_HPP

#include "device.hpp"

namespace kusengine
{
class SwapChain
{
public:
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    SwapChain() = default;

    void initSwapChain(Device* device_ptr, VkExtent2D windowExtent);

    ~SwapChain();

    SwapChain(const SwapChain&) = delete;

    void operator=(const SwapChain&) = delete;

    VkFramebuffer getFrameBuffer(int index);

    VkRenderPass getRenderPass();
    // VkImageView getImageView(int index)
    // {
    //     return swapChainImageViews[index];
    // }
    size_t imageCount();
    // {
    //     return swapChainImages.size();
    // }
    // VkFormat getSwapChainImageFormat()
    // {
    //     return swapChainImageFormat;
    // }
    VkExtent2D getSwapChainExtent();

    uint32_t width();
    uint32_t height();

    float extentAspectRatio();
    VkFormat findDepthFormat();

    void acquireNextImage(uint32_t* image_index);
    void submitCommandBuffers(const std::vector<VkCommandBuffer>& buffers,
                              uint32_t* image_index);

private:
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();
    void createSyncObjects();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats);

    // VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&
    // capabilities);

    VkFormat m_swap_chain_image_format;
    VkExtent2D m_swap_chain_extent;

    std::vector<VkFramebuffer> m_swap_chain_framebuffers;
    VkRenderPass m_render_pass;

    // std::vector<VkImage> depthImages;
    // std::vector<VkDeviceMemory> depthImageMemorys;
    // std::vector<VkImageView> depthImageViews;
    std::vector<VkImage> m_swap_chain_images;
    std::vector<VkImageView> m_swap_chain_image_views;

    Device* m_device_ptr;
    VkExtent2D m_window_extent;
    VkSwapchainKHR m_swap_chain;

    VkSemaphore m_submit_semaphore;
    VkSemaphore m_acuire_semaphore;
    VkFence m_img_available_fence;

    size_t currentFrame = 0;
};
}; // namespace kusengine

#endif // SWAP_CHAIN_HPP
