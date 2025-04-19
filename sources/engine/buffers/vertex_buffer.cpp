#include "vertex_buffer.hpp"

namespace kusengine
{

VertexBuffer::VertexBuffer(const Device& device) : Buffer(device)
{
}

void
VertexBuffer::create(size_t size)
{
    Buffer::create(size, vk::BufferUsageFlagBits::eVertexBuffer);
}

void
VertexBuffer::setVerteces(const std::vector<float>& verteces)
{
    Buffer::setData(verteces.data());
}
}; // namespace kusengine
