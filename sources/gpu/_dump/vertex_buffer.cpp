// #include "vertex_buffer.hpp"

// #include <vector>

// #include "kernel/framework/logger/basic/include_me.hpp"

// namespace gpu::logic
// {

// VertexBuffer::VertexBuffer(logic::Device a_device,
//                            const std::vector<Vertex>& a_vertices)
//     : VertexBuffer(a_device,
//                    reinterpret_cast<const char*>(a_vertices.data()),
//                    sizeof(a_vertices[0]) * a_vertices.size())
// {
// }

// VertexBuffer::VertexBuffer(logic::Device a_device,
//                            const char* a_data,
//                            vk::DeviceSize a_size)
// {
//     SCOPED_TRACE_CREATE("vertex buffer");

//     createBuffer(a_device, a_size, vk::BufferUsageFlagBits::eVertexBuffer,
//                  vk::MemoryPropertyFlagBits::eHostVisible |
//                      vk::MemoryPropertyFlagBits::eHostCoherent);

//     auto mem = a_device.mapMemory(*m_allocated_memory, 0, a_size,
//                                   static_cast<vk::MemoryMapFlags>(0));
//     memcpy(mem, a_data,
//            static_cast<size_t>(a_size)); // TODO: make it safe
//     a_device.unmapMemory(*m_allocated_memory);
// }

// void
// VertexBuffer::createBuffer(logic::Device a_device,
//                            vk::DeviceSize a_size,
//                            vk::BufferUsageFlags a_usage,
//                            vk::MemoryPropertyFlags a_properties)
// {
//     SCOPED_TRACE_CREATE("buffer");

//     vk::BufferCreateInfo create_info;
//     create_info.setSize(a_size).setUsage(a_usage).setSharingMode(
//         vk::SharingMode::eExclusive);

//     m_buffer     = a_device.createBufferUnique(create_info);
//     auto mem_req = a_device.getBufferMemoryRequirements(*m_buffer);
//     LOG_TRACE("Buffer requires %d bytes", mem_req.size);

//     auto mem_index =
//         a_device.getMemoryTypeIndex(mem_req.memoryTypeBits, a_properties);
//     LOG_TRACE("Memory type index %d", mem_index);
//     vk::MemoryAllocateInfo alloc_info;
//     alloc_info.setAllocationSize(mem_req.size).setMemoryTypeIndex(mem_index);

//     m_allocated_memory = a_device.allocateMemoryUnique(alloc_info);
//     a_device.bindBufferMemory(*m_buffer, *m_allocated_memory, 0);
// }

// void
// VertexBuffer::draw(vk::UniqueCommandBuffer& a_commands)
// {
//     a_commands->draw(m_vertex_count, 1, 0, 0);
// }

// void
// VertexBuffer::bind(vk::UniqueCommandBuffer& a_commands)
// {
//     static std::vector<vk::Buffer> buffers     = {*m_buffer};
//     static std::vector<vk::DeviceSize> offsets = {0};

//     a_commands->bindVertexBuffers(0, buffers, offsets);
// }

// } // namespace gpu::logic
