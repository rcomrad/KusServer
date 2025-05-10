#ifndef GPU_BUFFER_HPP
#define GPU_BUFFER_HPP

#include "engine/commands/command_buffer.hpp"

#include "buffer.hpp"
#include "staging_buffer.hpp"

namespace kusengine
{
class GpuVertexBuffer : public Buffer
{
public:
    GpuVertexBuffer();

    void bind(const vk::CommandBuffer& command_buffer) const;

    template <typename T>
    void setDataTrowStagingBuffer(T data, const vk::DeviceSize& byte_size);

    template <typename T>
    void setData(T data, const vk::DeviceSize& byte_size) = delete;

private:
};

template <typename T>
void
GpuVertexBuffer::setDataTrowStagingBuffer(T data,
                                          const vk::DeviceSize& byte_size)
{
    CommandBuffer command_buffer;
    command_buffer.create();

    StagingBuffer staging_buffer;
    staging_buffer.setData(data, byte_size);

    Buffer::copyBuffer(&staging_buffer, this, DEVICE.getQueue("graphics"),
                       command_buffer.commandBuffer());
}

}; // namespace kusengine

#endif // GPU_BUFFER_HPP
