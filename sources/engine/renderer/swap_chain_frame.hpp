#ifndef SWAP_CHAIN_FRAME_HPP
#define SWAP_CHAIN_FRAME_HPP

#include <vulkan/vulkan.hpp>

#include "engine/commands/command_buffer.hpp"

#include "render_pass.hpp"
#include "synchronization_control.hpp"

namespace kusengine
{
class SwapChain;

class SwapChainFrame
{
public:
    SwapChainFrame() = default;

    bool createFrameBuffer(const vk::Device& logical_device,
                           const vk::RenderPass& render_pass,
                           const vk::Extent2D& extent);

    const CommandBuffer& commandBuffer() const;

    const SynchronizationControl& synControl() const;

    const vk::Framebuffer& framebuffer() const;

    // Image part
    void createImage(const vk::Device& logical_device,
                     const vk::Image& image,
                     const vk::Format& format);

    void createSynchronization(const Device& device);

    // Command Buffer
    void createCommandBuffer(const CommandPool& command_pool);

    void waitForFence(const vk::Device& logical_device);

    // void recordCommandBuffer(const RenderPass& render_pass,
    //                          const SwapChain& swap_chain);

    void submitCommandBuffer(const Device& device);

private:
    SynchronizationControl m_sync_control;
    CommandBuffer m_command_buffer;

    //
    vk::UniqueFramebuffer m_framebuffer;

    // vk::UniqueImage m_image;
    vk::UniqueImageView m_view;
};
}; // namespace kusengine
#endif // SWAP_CHAIN_FRAME_HPP
