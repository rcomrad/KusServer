#include "buffer.hpp"

namespace kusengine
{

Buffer::Buffer(const Device& device) : device_ref(device)
{
}

uint32_t
Buffer::findMemoryTypeIndex(uint32_t supported_memory_indices,
                            vk::MemoryPropertyFlags requested_properties)
{
    vk::PhysicalDeviceMemoryProperties memoryProperties =
        device_ref.physicalDeviceConstRef().getMemoryProperties();

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
        device_ref.logicalDeviceConstRef().getBufferMemoryRequirements(
            m_buffer.get());

    vk::MemoryAllocateInfo allocInfo;
    allocInfo.allocationSize = memory_requirements.size;
    allocInfo.memoryTypeIndex =
        findMemoryTypeIndex(memory_requirements.memoryTypeBits,
                            vk::MemoryPropertyFlagBits::eHostVisible |
                                vk::MemoryPropertyFlagBits::eHostCoherent);

    m_memory =
        device_ref.logicalDeviceConstRef().allocateMemoryUnique(allocInfo);

    device_ref.logicalDeviceConstRef().bindBufferMemory(m_buffer.get(),
                                                        m_memory.get(), 0);
}

void
Buffer::create(size_t size, vk::BufferUsageFlags usage)
{
    vk::BufferCreateInfo bufferInfo;
    bufferInfo.flags       = vk::BufferCreateFlags();
    bufferInfo.size        = size;
    bufferInfo.usage       = usage;
    bufferInfo.sharingMode = vk::SharingMode::eExclusive;

    m_buffer =
        device_ref.logicalDeviceConstRef().createBufferUnique(bufferInfo);

    allocateBufferMemory();
}
}; // namespace kusengine
