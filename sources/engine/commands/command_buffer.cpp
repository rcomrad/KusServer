#include "command_buffer.hpp"

namespace kusengine
{
CommandBuffer::CommandBuffer()
{
}

void
CommandBuffer::create(const CommandPool& command_pool)
{
    m_command_buffer = command_pool.allocateCommandBuffer();
}

const vk::CommandBuffer&
CommandBuffer::commandBuffer() const
{
    return m_command_buffer.get();
}
}; // namespace kusengine
