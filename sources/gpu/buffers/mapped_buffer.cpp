#include "mapped_buffer.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include <vector>

gpu::buffer::MappedBuffer::MappedBuffer(logic::Device& a_device,
                                        vk::DeviceSize a_size,
                                        type::MemoryTypeBits a_type_filter,
                                        vk::MemoryPropertyFlags a_properties)
    : BaseBuffer(a_device, a_size, a_type_filter, a_properties),
      m_size(a_size),
      m_cur_bound(0)
{
    m_mapped_memory = mapMemory();
}

gpu::buffer::MappedBuffer::~MappedBuffer()
{
    unmapMemory();
}

void
gpu::buffer::MappedBuffer::push(const char* a_data, vk::DeviceSize a_size)
{
    if (m_cur_bound + a_size >= m_size)
    {
        THROW("Out of memory during writing (base buffer implementation)");
    }

    memcpy(m_mapped_memory + m_cur_bound, a_data,
           static_cast<size_t>(a_size)); // TODO: make it safe
    m_cur_bound += a_size;
}

void
gpu::buffer::MappedBuffer::clear()
{
    m_cur_bound = 0;
}
