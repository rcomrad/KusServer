#include "uniform_buffer.hpp"

namespace kusengine
{
namespace render
{
UniformBuffer::UniformBuffer()
    : Buffer(vk::BufferUsageFlagBits::eUniformBuffer,
             vk::MemoryPropertyFlagBits::eHostVisible |
                 vk::MemoryPropertyFlagBits::eHostCoherent)
{
}
}; // namespace render
}; // namespace kusengine
