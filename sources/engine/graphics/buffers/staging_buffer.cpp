#include "staging_buffer.hpp"

namespace kusengine
{

StagingBuffer::StagingBuffer()
    : Buffer(vk::BufferUsageFlagBits::eTransferSrc,
             vk::MemoryPropertyFlagBits::eHostVisible |
                 vk::MemoryPropertyFlagBits::eHostCoherent)
{
}

}; // namespace kusengine
