#include "uniform_buffer.hpp"

namespace kusengine
{

UniformBuffer::UniformBuffer()
    : Buffer(vk::BufferUsageFlagBits::eUniformBuffer,
             vk::MemoryPropertyFlagBits::eHostVisible |
                 vk::MemoryPropertyFlagBits::eHostCoherent)
{
}

}; // namespace kusengine
