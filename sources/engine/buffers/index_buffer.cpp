#include "index_buffer.hpp"

namespace kusengine
{

IndexBuffer::IndexBuffer()
    : Buffer(vk::BufferUsageFlagBits::eIndexBuffer,
             vk::MemoryPropertyFlagBits::eHostVisible |
                 vk::MemoryPropertyFlagBits::eHostCoherent)
{
}

void
IndexBuffer::bind(const vk::CommandBuffer& command_buffer) const
{
    command_buffer.bindIndexBuffer(buffer(), 0, vk::IndexType::eUint32);
}

void
IndexBuffer::draw(const vk::CommandBuffer& command_buffer,
                  uint32_t index_count) const
{
    command_buffer.drawIndexed(index_count, 1, 0, 0, 0);
}
}; // namespace kusengine
