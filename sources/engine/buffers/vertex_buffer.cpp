#include "vertex_buffer.hpp"

namespace kusengine
{

VertexBuffer::VertexBuffer(const Device& device) : Buffer(device)
{
}
void
VertexBuffer::checkBufferSize(size_t required_size)
{
    if (required_size > Buffer::size())
    {
        Buffer::recreate(vk::BufferUsageFlagBits::eVertexBuffer, required_size);
    }
}

void
VertexBuffer::setVertices(const std::initializer_list<float>& vertices)
{
    checkBufferSize(vertices.size() * sizeof(float));
    Buffer::setData(vertices.begin());
}

void
VertexBuffer::setVertices(const std::vector<float>& vertices)
{
    checkBufferSize(vertices.size() * sizeof(float));
    Buffer::setData(vertices.data());
}

void
VertexBuffer::bind(const vk::CommandBuffer& command_buffer) const
{
    vk::DeviceSize offsets[] = {0};
    command_buffer.bindVertexBuffers(0, 1, &(m_buffer.get()), offsets);
}
}; // namespace kusengine
