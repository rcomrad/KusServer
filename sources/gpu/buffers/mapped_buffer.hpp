#pragma once

#include "base_buffer.hpp"

namespace gpu::buffer
{

class MappedBuffer : public BaseBuffer
{
public:
    MappedBuffer(logic::Device& a_device,
                 vk::DeviceSize a_size,
                 type::MemoryTypeBits a_type_filter,
                 vk::MemoryPropertyFlags a_properties);
    ~MappedBuffer();

    void push(const char* a_data, vk::DeviceSize a_size);
    void clear();

private:
    vk::DeviceSize m_size;
    vk::DeviceSize m_cur_bound;
    char* m_mapped_memory;
};

} // namespace gpu::buffer
