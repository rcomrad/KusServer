#include "command_buffer.hpp"

#include "command_pool.hpp"
namespace kusengine
{
CommandBuffer::CommandBuffer()
{
}

void
CommandBuffer::create()
{
    m_command_buffer = COMMAND_POOL.allocateCommandBuffer();
}

const vk::CommandBuffer&
CommandBuffer::commandBuffer() const
{
    return m_command_buffer.get();
}
}; // namespace kusengine
