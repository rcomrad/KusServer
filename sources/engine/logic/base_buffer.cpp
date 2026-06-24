#include "base_buffer.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include <vector>

namespace engine::logic
{

BaseBuffer::BaseBuffer(logic::Device& a_device,
                       vk::DeviceSize a_size,
                       type::MemoryTypeBits a_type_filter,
                       vk::MemoryPropertyFlags a_properties)
    : m_device(a_device), m_size(a_size), m_cur_bind(0)
{

    SCOPED_TRACE_CREATE("base buffer (memory allocation)");
    LOG_DEBUG("Buffer requires %d bytes", a_size);

    vk::MemoryAllocateInfo alloc_info;
    auto mem_index = m_device.getMemoryTypeIndex(a_type_filter, a_properties);
    alloc_info.setAllocationSize(m_size).setMemoryTypeIndex(mem_index);

    m_allocated_memory = m_device.allocateMemoryUnique(alloc_info);
}

void
BaseBuffer::bind(vk::UniqueBuffer& a_buffer)
{
    const auto req   = m_device.getBufferMemoryRequirements(*a_buffer);
    const auto& size = req.size;

    if (m_cur_bind + size > m_size)
    {
        THROW("Out of memory during binding (base buffer implementation)");
    }

    m_device.bindBufferMemory(*a_buffer, *m_allocated_memory, m_cur_bind);
    m_cur_bind += size;
}

void
BaseBuffer::bind(vk::UniqueImage& a_image)
{
    const auto req   = m_device.getImageMemoryRequirements(*a_image);
    const auto& size = req.size;

    if (m_cur_bind + size > m_size)
    {
        THROW("Out of memory during binding (base buffer implementation)");
    }

    m_device.bindImageMemory(*a_image, *m_allocated_memory, m_cur_bind);
    m_cur_bind += size;
}

char*
BaseBuffer::mapMemory()
{
    return static_cast<char*>(m_device.mapMemory(
        *m_allocated_memory, 0, m_size, static_cast<vk::MemoryMapFlags>(0)));
}

void
BaseBuffer::unmapMemory()
{
    m_device.unmapMemory(*m_allocated_memory);
}

} // namespace engine::logic
