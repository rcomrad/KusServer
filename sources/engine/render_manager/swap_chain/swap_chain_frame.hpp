#ifndef SWAP_CHAIN_FRAME_HPP
#define SWAP_CHAIN_FRAME_HPP

#include <vulkan/vulkan.hpp>

#include <unordered_map>

#include "engine/render_manager/buffers/storage_buffer.hpp"
#include "engine/render_manager/buffers/uniform_buffer.hpp"
#include "engine/render_manager/commands/command_buffer.hpp"
#include "engine/render_manager/textures/image.hpp"

#include "synchronization_control.hpp"

namespace kusengine::render
{
class SwapChain;
class DescriptorAllocator;

class SwapChainFrame
{
public:
    const vk::CommandBuffer& commandBuffer() const& noexcept;

    const SynchronizationControl& synControl() const& noexcept;

    void addFrameBuffer(std::string_view key,
                        const vk::RenderPass& render_pass,
                        const vk::Extent2D& extent);

    const vk::Framebuffer& getBuffer(const std::string& key) const&;

    void setupImages(const vk::Image& image,
                     const vk::Format& format,
                     const vk::Extent2D& extent);

    void setupSynchronization();

    void setupCommandBuffer();

    // Resourcers

    //
    void waitForFence();

    void submitCommandBuffer();

private:
    void setupDepth(const vk::Extent2D& extent);

    SynchronizationControl m_sync_control;
    CommandBuffer m_command_buffer;

    //
    std::unordered_map<std::string, vk::UniqueFramebuffer> m_framebuffers;

    vk::UniqueImageView m_view;

    // depth
    Image m_depth_image;
};

}; // namespace kusengine::render
#endif // SWAP_CHAIN_FRAME_HPP
