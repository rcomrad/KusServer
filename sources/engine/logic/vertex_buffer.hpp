#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/logic/device.hpp"

#include "vertix.hpp"

namespace engine::logic
{

class VertexBuffer
{
public:
    VertexBuffer(logic::Device a_device, const std::vector<Vertex>& a_vertices);

    void bind(vk::UniqueCommandBuffer& a_commands);
    void draw(vk::UniqueCommandBuffer& a_commands);

private:
    vk::UniqueBuffer m_buffer;
    vk::UniqueDeviceMemory m_allocated_memory;

    uint32_t m_vertex_count;

    void createBuffer(logic::Device a_device,
                      vk::DeviceSize a_size,
                      vk::BufferUsageFlags a_usage,
                      vk::MemoryPropertyFlags a_properties);
};

} // namespace engine::logic
