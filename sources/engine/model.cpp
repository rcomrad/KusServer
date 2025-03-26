#include "model.hpp"

#include "engine_util.hpp"

namespace kusengine
{

Model::Model(Device* device,
             const std::vector<Vertex>& vertices,
             const std::vector<uint16_t>& indices)
    : m_indices(indices), m_device_ptr(device)
{
    m_texture_storage.loadTextures(m_device_ptr);

    m_texture_count = m_texture_storage.getTextureCount();

    createDescriptorSetLayout(m_texture_storage.getTextureCount());
    createSampler();
    createDescriptorPool();
    createDescriptorSet();
    updateDescriptorSet();

    createVertexBuffer(vertices);
    createIndexBuffer(indices);
}
Model::~Model()
{
    vkDestroyBuffer(m_device_ptr->device(), m_vertex_buffer.m_buffer, nullptr);
    vkFreeMemory(m_device_ptr->device(), m_vertex_buffer.m_memory, nullptr);
}

const VkDescriptorSetLayout*
Model::getSetLayoutsConstPtr()
{
    return &m_set_layout;
}

void
Model::createIndexBuffer(const std::vector<uint16_t>& indices)
{
    m_indices = indices;

    uint32_t index_count = static_cast<uint32_t>(m_indices.size());

    VkDeviceSize buffer_size = sizeof(m_indices[0]) * index_count;

    m_device_ptr->createBuffer(buffer_size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                               m_index_buffer.m_buffer,
                               m_index_buffer.m_memory);

    void* data;
    vkMapMemory(m_device_ptr->device(), m_index_buffer.m_memory, 0, buffer_size,
                0, &data);
    memcpy(data, m_indices.data(), static_cast<size_t>(buffer_size));
    vkUnmapMemory(m_device_ptr->device(), m_index_buffer.m_memory);
}

void
Model::createVertexBuffer(const std::vector<Vertex>& vertices)
{
    m_vertices = vertices;

    uint32_t vertex_count = static_cast<uint32_t>(m_vertices.size());

    VkDeviceSize buffer_size = sizeof(m_vertices[0]) * vertex_count;

    m_device_ptr->createBuffer(buffer_size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                               m_vertex_buffer.m_buffer,
                               m_vertex_buffer.m_memory);

    updateVertexBuffer();
}

void
Model::updateVertexBuffer()
{
    VkDeviceSize buffer_size =
        sizeof(m_vertices[0]) * static_cast<uint32_t>(m_vertices.size());

    void* data;
    vkMapMemory(m_device_ptr->device(), m_vertex_buffer.m_memory, 0,
                buffer_size, 0, &data);
    memcpy(data, m_vertices.data(), static_cast<size_t>(buffer_size));
    vkUnmapMemory(m_device_ptr->device(), m_vertex_buffer.m_memory);
}

void
Model::draw(VkCommandBuffer command_buffer)
{
    vkCmdDraw(command_buffer, static_cast<uint32_t>(m_vertices.size()), 1, 0,
              0);
    vkCmdDrawIndexed(command_buffer, static_cast<uint32_t>(m_indices.size()), 1,
                     0, 0, 0);
}

void
Model::bind(VkCommandBuffer command_buffer, VkPipelineLayout& pipelayout)
{
    VkBuffer buffers[]     = {m_vertex_buffer.m_buffer};
    VkDeviceSize offsets[] = {0};

    vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                            pipelayout, 0, 1, &m_descriptor_set, 0, 0);
    vkCmdBindVertexBuffers(command_buffer, 0, 1, buffers, offsets);
    vkCmdBindIndexBuffer(command_buffer, m_index_buffer.m_buffer, 0,
                         VK_INDEX_TYPE_UINT16);
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
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);
    attributeDescriptions[0].binding  = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format   = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset   = offsetof(Vertex, position);

    attributeDescriptions[1].binding  = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format   = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[1].offset   = offsetof(Vertex, uv);

    attributeDescriptions[2].binding  = 0;
    attributeDescriptions[2].location = 2;
    attributeDescriptions[2].format   = VK_FORMAT_R32_SINT;
    attributeDescriptions[2].offset   = offsetof(Vertex, texture_index);
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

void
Model::createSampler()
{
    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType               = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.minFilter           = VK_FILTER_NEAREST;
    samplerInfo.magFilter           = VK_FILTER_NEAREST;
    samplerInfo.addressModeU        = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV        = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW        = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;

    /////////////////////////
    samplerInfo.maxAnisotropy           = 16.0f;
    samplerInfo.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable           = VK_FALSE;
    samplerInfo.compareOp               = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias              = 0.0f; // Укажите LOD Bias здесь

    vkCreateSampler(m_device_ptr->device(), &samplerInfo, 0, &m_sampler);
}

void
Model::createDescriptorSetLayout(uint32_t textures_count)
{
    std::vector<VkDescriptorSetLayoutBinding> layout_bindings = {
        engine_util::layout_binding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                                    VK_SHADER_STAGE_FRAGMENT_BIT,
                                    textures_count, 0)};

    VkDescriptorSetLayoutCreateInfo layout_info = {};
    layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layout_info.bindingCount = layout_bindings.size();
    layout_info.pBindings    = layout_bindings.data();

    vkCreateDescriptorSetLayout(m_device_ptr->device(), &layout_info, 0,
                                &m_set_layout);
}

void
Model::createDescriptorSet()
{
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType       = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.pSetLayouts = &m_set_layout;
    allocInfo.descriptorSetCount = 1;
    allocInfo.descriptorPool     = m_descriptor_pool;
    vkAllocateDescriptorSets(m_device_ptr->device(), &allocInfo,
                             &m_descriptor_set);
}

void
Model::createDescriptorPool()
{
    std::vector<VkDescriptorPoolSize> poolSizes = {
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, m_texture_count},
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1              },
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1              }
    };

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.maxSets       = 1;
    poolInfo.poolSizeCount = poolSizes.size();
    poolInfo.pPoolSizes    = poolSizes.data();
    vkCreateDescriptorPool(m_device_ptr->device(), &poolInfo, 0,
                           &m_descriptor_pool);
}

void
Model::updateDescriptorSet()
{
    std::vector<VkDescriptorImageInfo> image_info(m_texture_count, {});
    image_info[0].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info[0].imageView   = m_texture_storage.getTexture("cat.dds");
    image_info[0].sampler     = m_sampler;

    image_info[1].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info[1].imageView   = m_texture_storage.getTexture("eye.dds");
    image_info[1].sampler     = m_sampler;

    image_info[2].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info[2].imageView   = m_texture_storage.getTexture("red_eye.dds");
    image_info[2].sampler     = m_sampler;

    VkWriteDescriptorSet write{};
    write.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet          = m_descriptor_set;
    write.pImageInfo      = image_info.data();
    write.dstBinding      = 0;
    write.descriptorCount = m_texture_storage.getTextureCount();
    write.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

    vkUpdateDescriptorSets(m_device_ptr->device(), 1, &write, 0, 0);
}

}; // namespace kusengine
