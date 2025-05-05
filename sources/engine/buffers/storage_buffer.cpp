#include "storage_buffer.hpp"

namespace kusengine
{

StorageBuffer::StorageBuffer()
    : Buffer(vk::BufferUsageFlagBits::eStorageBuffer,
             vk::MemoryPropertyFlagBits::eHostVisible |
                 vk::MemoryPropertyFlagBits::eHostCoherent)
{
}

}; // namespace kusengine
