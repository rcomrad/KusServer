// #include "increment_buffer.hpp"

// #include <vector>

// #include "kernel/framework/logger/basic/include_me.hpp"

// namespace engine::logic
// {

// IncrementBuffer::IncrementBuffer(logic::Device& a_device, vk::DeviceSize a_size)
//     : m_device(a_device), m_size(a_size), m_cur_bound(0)
// {
//     m_buffer =
//         createBuffer(m_device, m_size, vk::BufferUsageFlagBits::eVertexBuffer);
//     m_allocated_memory =
//         allocateMemory(m_device, m_buffer,
//                        vk::MemoryPropertyFlagBits::eHostVisible |
//                            vk::MemoryPropertyFlagBits::eHostCoherent);
//     m_device.bindBufferMemory(*m_buffer, *m_allocated_memory, 0);

//     m_mapped_memory = m_device.mapMemory(*m_allocated_memory, 0, a_size,
//                                          static_cast<vk::MemoryMapFlags>(0));

//     m_buffers_for_bind = {*m_buffer};
//     m_offsets_for_bind = {0};
// }

// IncrementBuffer::~IncrementBuffer()
// {
//     m_device.unmapMemory(*m_allocated_memory);
// }

// vk::UniqueBuffer
// IncrementBuffer::createBuffer(logic::Device& a_device,
//                               vk::DeviceSize a_size,
//                               vk::BufferUsageFlags a_usage)
// {
//     SCOPED_TRACE_CREATE("buffer");

//     vk::BufferCreateInfo create_info;
//     create_info.setSize(a_size).setUsage(a_usage).setSharingMode(
//         vk::SharingMode::eExclusive);

//     return a_device.createBufferUnique(create_info);
// }

// vk::UniqueDeviceMemory
// IncrementBuffer::allocateMemory(logic::Device& a_device,
//                                 vk::UniqueBuffer& a_buffer,
//                                 vk::MemoryPropertyFlags a_properties)
// {
//     SCOPED_TRACE_CREATE("allocator");

//     auto mem_req = a_device.getBufferMemoryRequirements(*a_buffer);
//     LOG_TRACE("Buffer requires %d bytes", mem_req.size);

//     auto mem_index =
//         a_device.getMemoryTypeIndex(mem_req.memoryTypeBits, a_properties);
//     LOG_TRACE("Memory type index %d", mem_index);
//     vk::MemoryAllocateInfo alloc_info;
//     alloc_info.setAllocationSize(mem_req.size).setMemoryTypeIndex(mem_index);

//     return a_device.allocateMemoryUnique(alloc_info);
// }

// void
// IncrementBuffer::push(const char* a_data, vk::DeviceSize a_size)
// {
//     memcpy(m_mapped_memory + m_cur_bound, a_data,
//            static_cast<size_t>(a_size)); // TODO: make it safe
//     m_cur_bound += a_size;
// }

// void
// IncrementBuffer::bind(logic::BasicCommand& a_commands)
// {
//     a_commands.bindIncrementBuffers(0, m_buffers_for_bind, m_offsets_for_bind);
// }

// } // namespace engine::logic
