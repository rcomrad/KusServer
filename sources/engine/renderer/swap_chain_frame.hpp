#ifndef SWAP_CHAIN_FRAME_HPP
#define SWAP_CHAIN_FRAME_HPP

#include <vulkan/vulkan.hpp>

#include "engine/buffers/storage_buffer.hpp"
#include "engine/buffers/uniform_buffer.hpp"
#include "engine/commands/command_buffer.hpp"
#include "engine/descriptors/descriptor_manager.hpp"
#include "engine/render_objects/objects_data/model_basic_dynamics_data.hpp"
#include "engine/render_objects/objects_data/uniform_buffer_object.hpp"

#include "synchronization_control.hpp"

namespace kusengine
{
class SwapChain;

class SwapChainFrame
{
public:
    SwapChainFrame() = default;

    bool createFrameBuffer(const vk::RenderPass& render_pass,
                           const vk::Extent2D& extent);

    const CommandBuffer& commandBuffer() const;

    const SynchronizationControl& synControl() const;

    const vk::Framebuffer& framebuffer() const;

    // Image part
    void createImage(const vk::Image& image, const vk::Format& format);

    void createSynchronization();

    // Command Buffer
    void createCommandBuffer();

    void waitForFence();

    void submitCommandBuffer();

    // Resourcers

    void updateUniformData(const UBO& ubo);

    void updateMBDD(const std::vector<MBDD>& data);

    void createDescriptorSet(const DescriptorManager& descriptor_manager);

    void writeDescriptorSetUBO();
    void writeDescriptorSetMBDD();

    std::vector<vk::DescriptorSet> descriptorSets() const;

private:
    SynchronizationControl m_sync_control;
    CommandBuffer m_command_buffer;

    //
    vk::UniqueFramebuffer m_framebuffer;

    vk::UniqueImageView m_view;

    // Resources

    UniformBuffer m_uniform_buffer;
    std::vector<vk::UniqueDescriptorSet> m_descriptor_sets;

    StorageBuffer m_storage_buffer;
};
}; // namespace kusengine
#endif // SWAP_CHAIN_FRAME_HPP
