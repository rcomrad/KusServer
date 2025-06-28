#include "storage_buffer.hpp"

namespace kusengine
{
namespace render
{
StorageBuffer::StorageBuffer()
    : Buffer(vk::BufferUsageFlagBits::eStorageBuffer,
             vk::MemoryPropertyFlagBits::eHostVisible |
                 vk::MemoryPropertyFlagBits::eHostCoherent)
{
}
}; // namespace render
}; // namespace kusengine
