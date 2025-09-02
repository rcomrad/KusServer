#include "gpu_buffer.hpp"

#include <iostream>

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

void
GpuVertexBuffer::setData(void* data, const vk::DeviceSize& byte_size)
{
    CommandBuffer command_buffer;
    command_buffer.create();

    StagingBuffer staging_buffer;
    staging_buffer.setData(data, byte_size);

    Buffer::copyBuffer(&staging_buffer, this,
                       DEVICE_INSTANCE.getQueue("graphics"),
                       command_buffer.commandBuffer());
}

}; // namespace render
}; // namespace kusengine
