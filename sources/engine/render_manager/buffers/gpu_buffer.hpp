#ifndef GPU_BUFFER_HPP
#define GPU_BUFFER_HPP

#include "engine/render_manager/commands/command_buffer.hpp"

#include "buffer.hpp"
#include "staging_buffer.hpp"
#include "storage_buffer.hpp"

namespace kusengine
{

namespace render
{

class GpuVertexBuffer : public Buffer
{
public:
    GpuVertexBuffer();

    void bind(const vk::CommandBuffer& command_buffer) const;

    void setData(void* data, const vk::DeviceSize& byte_size);

private:
};

}; // namespace render
}; // namespace kusengine

#endif // GPU_BUFFER_HPP
