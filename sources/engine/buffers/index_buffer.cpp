#include "index_buffer.hpp"

namespace kusengine
{

void
IndexBuffer::checkBufferSize(size_t required_size)
{
    if (required_size > Buffer::size())
    {
        Buffer::recreate(vk::BufferUsageFlagBits::eIndexBuffer, required_size);
    }
}

void
IndexBuffer::setIndices(const std::initializer_list<uint32_t>& indices)
{
    checkBufferSize(indices.size() * sizeof(uint32_t));
    Buffer::setData(indices.begin());
}

void
IndexBuffer::setIndices(const std::vector<uint32_t>& indices)
{
    checkBufferSize(indices.size() * sizeof(uint32_t));
    Buffer::setData(indices.data());
}

void
IndexBuffer::bind(const vk::CommandBuffer& command_buffer) const
{
    vk::DeviceSize ds_offset = 0;
    command_buffer.bindIndexBuffer(m_buffer.get(), ds_offset,
                                   vk::IndexType::eUint32);
}

void
IndexBuffer::draw(const vk::CommandBuffer& command_buffer,
                  uint32_t index_count) const
{
    command_buffer.drawIndexed(index_count, 1, 0, 0, 0);
}
}; // namespace kusengine
