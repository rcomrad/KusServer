#include "buffer.hpp"

#include "engine/render_manager/textures/image.hpp"

namespace kusengine
{
namespace render
{
Buffer::Buffer(vk::BufferUsageFlags buffer_usage_flags,
               vk::MemoryPropertyFlags requested_properties)
    : m_byte_size(0),
      m_buffer_usage_flags(buffer_usage_flags),
      m_requested_properties(requested_properties)
{
}

const vk::Buffer&
Buffer::buffer() const
{
    return m_buffer.get();
}

void
Buffer::checkBufferSize(const vk::DeviceSize& required_size)
{
    if (required_size > Buffer::byteSize())
    {
        Buffer::recreate(required_size);
    }
}

void
Buffer::allocateBufferMemory()
{
    vk::MemoryRequirements memory_requirements =
        LOGICAL_DEVICE_INSTANCE.getBufferMemoryRequirements(m_buffer.get());

    vk::MemoryAllocateInfo allocInfo;
    allocInfo.allocationSize  = memory_requirements.size;
    allocInfo.memoryTypeIndex = DEVICE_INSTANCE.findMemoryTypeIndex(
        memory_requirements.memoryTypeBits, m_requested_properties);

    m_memory = LOGICAL_DEVICE_INSTANCE.allocateMemoryUnique(allocInfo);

    LOGICAL_DEVICE_INSTANCE.bindBufferMemory(m_buffer.get(), m_memory.get(), 0);
}

void
Buffer::recreate(const vk::DeviceSize& size)
{
    m_byte_size = size;

    vk::BufferCreateInfo bufferInfo;
    bufferInfo.flags       = vk::BufferCreateFlags();
    bufferInfo.size        = size;
    bufferInfo.usage       = m_buffer_usage_flags;
    bufferInfo.sharingMode = vk::SharingMode::eExclusive;

    m_buffer = LOGICAL_DEVICE_INSTANCE.createBufferUnique(bufferInfo);

    allocateBufferMemory();
}

vk::DeviceSize
Buffer::byteSize() const
{
    return m_byte_size;
}

void
Buffer::copyBuffer(const Buffer* const src_buffer,
                   Buffer* const dst_buffer,
                   vk::Queue queue,
                   const vk::CommandBuffer& command_buffer)
{
    command_buffer.reset();

    vk::CommandBufferBeginInfo beginInfo;
    beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
    command_buffer.begin(beginInfo);

    vk::BufferCopy copyRegion;
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size      = src_buffer->m_byte_size;

    dst_buffer->checkBufferSize(src_buffer->m_byte_size);
    command_buffer.copyBuffer(src_buffer->m_buffer.get(),
                              dst_buffer->m_buffer.get(), 1, &copyRegion);

    command_buffer.end();

    vk::SubmitInfo submitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = &command_buffer;
    queue.submit(1, &submitInfo, nullptr);
    queue.waitIdle();
}

void
Buffer::copyBufferToImage(const Buffer* const src_buffer,
                          Image& dst_image,
                          vk::Queue queue,
                          const vk::CommandBuffer& command_buffer,
                          float width,
                          float height)
{
    command_buffer.reset();

    vk::CommandBufferBeginInfo beginInfo;
    beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
    command_buffer.begin(beginInfo);

    vk::ImageMemoryBarrier barrier = dst_image.memoryBarrier();

    command_buffer.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe,
                                   vk::PipelineStageFlagBits::eTransfer, {}, 0,
                                   nullptr, 0, nullptr, 1, &barrier);

    vk::BufferImageCopy region(
        0, 0, 0, {vk::ImageAspectFlagBits::eColor, 0, 0, 1}, {0, 0, 0},
        {static_cast<uint32_t>(width), static_cast<uint32_t>(height), 1});

    dst_image.getDataFromBuffer(src_buffer->buffer(), command_buffer, region);

    barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
    barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;
    barrier.oldLayout     = vk::ImageLayout::eTransferDstOptimal;
    barrier.newLayout     = vk::ImageLayout::eShaderReadOnlyOptimal;

    command_buffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer,
                                   vk::PipelineStageFlagBits::eFragmentShader,
                                   {}, 0, nullptr, 0, nullptr, 1, &barrier);

    command_buffer.end();
}
}; // namespace render

}; // namespace kusengine
