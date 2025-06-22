#ifndef SWAP_CHAIN_FRAME_HPP
#define SWAP_CHAIN_FRAME_HPP

#include <vulkan/vulkan.hpp>

#include "engine/render_manager/buffers/storage_buffer.hpp"
#include "engine/render_manager/buffers/uniform_buffer.hpp"
#include "engine/render_manager/commands/command_buffer.hpp"
#include "engine/render_manager/descriptors/descriptor_manager.hpp"

#include "synchronization_control.hpp"

namespace kusengine
{
namespace render
{
class SwapChain;

class SwapChainFrame
{
public:
    SwapChainFrame() = default;

    void createFrameBuffer(const vk::RenderPass& render_pass,
                           const vk::Extent2D& extent);

    const vk::CommandBuffer& commandBuffer() const noexcept;

    const SynchronizationControl& synControl() const noexcept;

    const vk::Framebuffer& framebuffer() const noexcept;

    // Image part
    void createImage(const vk::Image& image, const vk::Format& format);

    void createSynchronization();

    // Command Buffer
    void createCommandBuffer();

    void waitForFence();

    void submitCommandBuffer();

    // Resourcers

    template <typename UBOType>
    void updateUBO(const UBOType& ubo)
    {
        m_uniform_buffer.setData(&ubo, sizeof(UBOType));
        writeDescriptorSetUBO();
    }
    template <typename MBDDType>
    void updateMBDD(const std::vector<MBDDType>& data)
    {
        m_storage_buffer.setData(data.data(), data.size() * sizeof(MBDDType));
        writeDescriptorSetMBDD();
    }

    void createDescriptorSet(const DescriptorManager& descriptor_manager);

    void writeDescriptorSetUBO();
    void writeDescriptorSetMBDD();

    const std::vector<vk::DescriptorSet>& descriptorSets() const noexcept;

private:
    SynchronizationControl m_sync_control;
    CommandBuffer m_command_buffer;

    //
    vk::UniqueFramebuffer m_framebuffer;

    vk::UniqueImageView m_view;

    // Resources

    UniformBuffer m_uniform_buffer;
    std::vector<vk::DescriptorSet> m_descriptor_sets;

    StorageBuffer m_storage_buffer;
};
}; // namespace render
}; // namespace kusengine
#endif // SWAP_CHAIN_FRAME_HPP
