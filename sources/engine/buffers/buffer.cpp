#include "buffer.hpp"

namespace kusengine
{

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
    allocInfo.allocationSize = memory_requirements.size;
    allocInfo.memoryTypeIndex =
        findMemoryTypeIndex(memory_requirements.memoryTypeBits,
                            vk::MemoryPropertyFlagBits::eHostVisible |
                                vk::MemoryPropertyFlagBits::eHostCoherent);

    m_memory = LOGICAL_DEVICE.allocateMemoryUnique(allocInfo);

    LOGICAL_DEVICE.bindBufferMemory(m_buffer.get(), m_memory.get(), 0);
}

void
Buffer::recreate(vk::BufferUsageFlags usage, size_t size)
{
    m_size = size;

    vk::BufferCreateInfo bufferInfo;
    bufferInfo.flags       = vk::BufferCreateFlags();
    bufferInfo.size        = size;
    bufferInfo.usage       = usage;
    bufferInfo.sharingMode = vk::SharingMode::eExclusive;

    m_buffer = LOGICAL_DEVICE.createBufferUnique(bufferInfo);

    allocateBufferMemory();
}

size_t
Buffer::size() const
{
    return m_size;
}

}; // namespace kusengine
