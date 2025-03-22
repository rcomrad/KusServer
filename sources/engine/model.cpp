#include "model.hpp"

namespace kusengine
{

Model::Model(Device* device, const std::vector<Vertex>& vertices)
    : m_device_ptr(device)
{
    createVertexBuffer(vertices);
}
Model::~Model()
{
    vkDestroyBuffer(m_device_ptr->device(), m_vertex_buffer, nullptr);
    vkFreeMemory(m_device_ptr->device(), m_vertex_buffer_memory, nullptr);
}

void
Model::createVertexBuffer(const std::vector<Vertex>& vertices)
{
    m_vertices = vertices;

    m_vertex_count = static_cast<uint32_t>(m_vertices.size());

    VkDeviceSize buffer_size = sizeof(m_vertices[0]) * m_vertex_count;

    m_device_ptr->createBuffer(buffer_size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                               m_vertex_buffer, m_vertex_buffer_memory);

    updateVertexBuffer();
}

void
Model::updateVertexBuffer()
{
    VkDeviceSize buffer_size = sizeof(m_vertices[0]) * m_vertex_count;

    void* data;
    vkMapMemory(m_device_ptr->device(), m_vertex_buffer_memory, 0, buffer_size,
                0, &data);
    memcpy(data, m_vertices.data(), static_cast<size_t>(buffer_size));
    vkUnmapMemory(m_device_ptr->device(), m_vertex_buffer_memory);
}

void
Model::draw(VkCommandBuffer command_buffer)
{
    vkCmdDraw(command_buffer, m_vertex_count, 1, 0, 0);
}

void
Model::bind(VkCommandBuffer command_buffer)
{
    VkBuffer buffers[]     = {m_vertex_buffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(command_buffer, 0, 1, buffers, offsets);
}

std::vector<VkVertexInputBindingDescription>
Model::Vertex::getBindingDescriptions()
{
    std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
    bindingDescriptions[0].binding   = 0;
    bindingDescriptions[0].stride    = sizeof(Vertex);
    bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return bindingDescriptions;
}

std::vector<VkVertexInputAttributeDescription>
Model::Vertex::getAttributeDescriptions()
{
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
    attributeDescriptions[0].binding  = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format   = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset   = offsetof(Vertex, position);

    attributeDescriptions[1].binding  = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format   = VK_FORMAT_R32G32_SFLOAT;

    attributeDescriptions[1].offset = offsetof(Vertex, uv);
    return attributeDescriptions;
}

void
Model::move(float x, float y)
{
    for (auto& v : m_vertices)
    {
        v.position.x += x;
        v.position.y += y;
    }
    updateVertexBuffer();
}

}; // namespace kusengine
