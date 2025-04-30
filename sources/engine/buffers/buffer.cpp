#include "buffer.hpp"

#include "engine/device/device.hpp"

namespace kusengine
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

uint32_t
Buffer::findMemoryTypeIndex(uint32_t supported_memory_indices,
                            vk::MemoryPropertyFlags requested_properties)
{
    vk::PhysicalDeviceMemoryProperties memoryProperties =
        PHYSICAL_DEVICE.getMemoryProperties();

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        bool supported{static_cast<bool>(supported_memory_indices & (1 << i))};

        bool sufficient{(memoryProperties.memoryTypes[i].propertyFlags &
                         requested_properties) == requested_properties};

        if (supported && sufficient)
        {
            return i;
        }
    }

    return 0;
}

void
Buffer::allocateBufferMemory()
{
    vk::MemoryRequirements memory_requirements =
        LOGICAL_DEVICE.getBufferMemoryRequirements(m_buffer.get());

    vk::MemoryAllocateInfo allocInfo;
    allocInfo.allocationSize  = memory_requirements.size;
    allocInfo.memoryTypeIndex = findMemoryTypeIndex(
        memory_requirements.memoryTypeBits, m_requested_properties);

    m_memory = LOGICAL_DEVICE.allocateMemoryUnique(allocInfo);

    LOGICAL_DEVICE.bindBufferMemory(m_buffer.get(), m_memory.get(), 0);
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

    m_buffer = LOGICAL_DEVICE.createBufferUnique(bufferInfo);

    allocateBufferMemory();
}

vk::DeviceSize
Buffer::byteSize() const
{
    return m_byte_size;
}

void
Buffer::copyBuffer(Buffer& src_buffer,
                   Buffer& dst_buffer,
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
    copyRegion.size      = src_buffer.m_byte_size;

    dst_buffer.checkBufferSize(src_buffer.m_byte_size);
    command_buffer.copyBuffer(src_buffer.m_buffer.get(),
                              dst_buffer.m_buffer.get(), 1, &copyRegion);

    command_buffer.end();

    vk::SubmitInfo submitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = &command_buffer;
    queue.submit(1, &submitInfo, nullptr);
    queue.waitIdle();
}

}; // namespace kusengine
