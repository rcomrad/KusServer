#include "staging_buffer.hpp"

namespace kusengine
{
 namespace render{
StagingBuffer::StagingBuffer()
    : Buffer(vk::BufferUsageFlagBits::eTransferSrc,
             vk::MemoryPropertyFlagBits::eHostVisible |
                 vk::MemoryPropertyFlagBits::eHostCoherent)
{
}
}; // namespace render
}; // namespace kusengine
