#include "model.hpp"

namespace kusengine
{

Model::Model(Device* device, const std::vector<Vertex>& vertices)
    : m_device_ptr(device)
{
    createVertexBuffers(vertices);
}
Model::~Model()
{
    vkDestroyBuffer(m_device_ptr->device(), m_vertex_buffer, nullptr);
    vkFreeMemory(m_device_ptr->device(), m_vertex_buffer_memory, nullptr);
}

void
Model::createVertexBuffers(const std::vector<Vertex>& vertices)
{
    m_vertex_count = static_cast<uint32_t>(vertices.size());

    VkDeviceSize buffer_size = sizeof(vertices[0]) * m_vertex_count;

    m_device_ptr->createBuffer(buffer_size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                               m_vertex_buffer, m_vertex_buffer_memory);

    void* data;
    vkMapMemory(m_device_ptr->device(), m_vertex_buffer_memory, 0, buffer_size,
                0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(buffer_size));
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
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions(1);
    attributeDescriptions[0].binding  = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format   = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset   = 0;
    return attributeDescriptions;
}

}; // namespace kusengine
