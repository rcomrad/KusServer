#include "vertex_buffer.hpp"

namespace kusengine
{

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
    vk::DeviceSize ds_offsets[] = {0};

    command_buffer.bindVertexBuffers(0, 1, &(m_buffer.get()), ds_offsets);
}

void
VertexBuffer::draw(const vk::CommandBuffer& command_buffer,
                   uint32_t vertex_count,
                   uint32_t instance_count,
                   uint32_t first_vertex,
                   uint32_t first_instance) const
{
    command_buffer.draw(vertex_count, instance_count, first_vertex,
                        first_instance);
}
}; // namespace kusengine
