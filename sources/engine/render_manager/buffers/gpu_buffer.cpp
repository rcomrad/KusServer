#include "gpu_buffer.hpp"

namespace kusengine
{
namespace render
{
GpuVertexBuffer::GpuVertexBuffer()
    : Buffer(vk::BufferUsageFlagBits::eVertexBuffer |
                 vk::BufferUsageFlagBits::eTransferDst,
             vk::MemoryPropertyFlagBits::eDeviceLocal)
{
}

void
GpuVertexBuffer::bind(const vk::CommandBuffer& command_buffer) const
{
    vk::DeviceSize offsets = {0};
    command_buffer.bindVertexBuffers(0, 1, &(buffer()), &offsets);
}
}; // namespace render
}; // namespace kusengine
