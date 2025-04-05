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

const vk::DescriptorSetLayout*
Model::getSetLayoutsConstPtr()
{
    return &m_set_layout;
}

void
Model::createIndexBuffer(const std::vector<uint16_t>& indices)
{
    m_indices                        = indices;
    const vk::DeviceSize buffer_size = sizeof(indices[0]) * indices.size();

    // Buffer staging_buffer;

    m_device_ptr->createBuffer(
        buffer_size, vk::BufferUsageFlagBits::eTransferSrc,
        vk::MemoryPropertyFlagBits::eHostVisible |
            vk::MemoryPropertyFlagBits::eHostCoherent,
        staging_buffer.m_buffer.get(), staging_buffer.m_memory.get());

    void* data = m_device_ptr->device().mapMemory(staging_buffer.m_memory.get(),
                                                  0, buffer_size);

    memcpy(data, indices.data(), static_cast<size_t>(buffer_size));

    m_device_ptr->device().unmapMemory(staging_buffer.m_memory.get());

    m_device_ptr->createBuffer(buffer_size,
                               vk::BufferUsageFlagBits::eTransferDst |
                                   vk::BufferUsageFlagBits::eIndexBuffer,
                               vk::MemoryPropertyFlagBits::eDeviceLocal,
                               m_index_buffer.m_buffer.get(),
                               m_index_buffer.m_memory.get());

    m_device_ptr->copyBuffer(staging_buffer.m_buffer.get(),
                             m_index_buffer.m_buffer.get(), buffer_size);
}

void
Model::createVertexBuffer(const std::vector<Vertex>& vertices)
{
    m_vertices = vertices;

    uint32_t vertex_count = static_cast<uint32_t>(m_vertices.size());

    vk::DeviceSize buffer_size = sizeof(m_vertices[0]) * vertex_count;

    m_device_ptr->createBuffer(
        buffer_size, vk::BufferUsageFlagBits::eVertexBuffer,
        vk::MemoryPropertyFlagBits::eHostVisible |
            vk::MemoryPropertyFlagBits::eHostCoherent,
        m_vertex_buffer.m_buffer.get(), m_vertex_buffer.m_memory.get());

    updateVertexBuffer();
}

void
Model::updateVertexBuffer()
{
    vk::DeviceSize bufferSize = sizeof(m_vertices[0]) * m_vertices.size();

    void* data = m_device_ptr->device().mapMemory(
        m_vertex_buffer.m_memory.get(), 0, bufferSize, vk::MemoryMapFlags());
    memcpy(data, m_vertices.data(), static_cast<size_t>(bufferSize));
    m_device_ptr->device().unmapMemory(m_vertex_buffer.m_memory.get());
}

void
Model::draw(vk::CommandBuffer command_buffer)
{
    // command_buffer.draw(m_vertices.size(), 1, 0, 0);
    command_buffer.drawIndexed(m_indices.size(), 1, 0, 0, 0);
}

void
Model::bindVertexBuffer(vk::CommandBuffer command_buffer)
{
    vk::Buffer buffers[]     = {m_vertex_buffer.m_buffer.get()};
    vk::DeviceSize offsets[] = {0};

    command_buffer.bindVertexBuffers(0, 1, buffers, offsets);
}

void
Model::bindIndexBuffer(vk::CommandBuffer command_buffer)
{
    command_buffer.bindIndexBuffer(m_index_buffer.m_buffer.get(), 0,
                                   vk::IndexType::eUint16);
}

void
Model::bindDescriptorSets(vk::CommandBuffer command_buffer,
                          vk::PipelineLayout& pipeline_layout)
{
    command_buffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                      pipeline_layout, 0, 1, &m_descriptor_set,
                                      0, 0);
}

std::vector<vk::VertexInputBindingDescription>
Model::Vertex::getBindingDescriptions()
{
    return {
        vk::VertexInputBindingDescription{
                                          0,                           // binding
            sizeof(Vertex),              // stride
            vk::VertexInputRate::eVertex // inputRate
        }
    };
}

std::vector<vk::VertexInputAttributeDescription>
Model::Vertex::getAttributeDescriptions()
{
    return {
        {0, 0, vk::Format::eR32G32Sfloat,
         static_cast<uint32_t>(offsetof(Vertex, position))     },
        {1, 0, vk::Format::eR32G32Sfloat,
         static_cast<uint32_t>(offsetof(Vertex, uv))           },
        {2, 0, vk::Format::eR32Sint,

         static_cast<uint32_t>(offsetof(Vertex, texture_index))}
    };
}

void
Model::createSampler()
{
    vk::SamplerCreateInfo sampler_info(
        {},                                   // flags
        vk::Filter::eNearest,                 // minFilter
        vk::Filter::eNearest,                 // magFilter
        vk::SamplerMipmapMode::eLinear,       // mipmapMode
        vk::SamplerAddressMode::eClampToEdge, // addressModeU
        vk::SamplerAddressMode::eClampToEdge, // addressModeV
        vk::SamplerAddressMode::eClampToEdge, // addressModeW
        0.0f,                                 // mipLodBias
        vk::False,                            // anisotropyEnable
        16.0f,                                // maxAnisotropy
        false,                                // compareEnable
        vk::CompareOp::eAlways,               // compareOp
        0.0f,                                 // minLod
        0.0f,                                 // maxLod
        vk::BorderColor::eIntOpaqueBlack,     // borderColor
        false                                 // unnormalizedCoordinates
    );

    m_sampler = m_device_ptr->device().createSampler(sampler_info);
}

void
Model::createDescriptorSetLayout(uint32_t textures_count)
{
    std::vector<vk::DescriptorSetLayoutBinding> layout_bindings = {
        engine_util::createLayoutBinding(
            vk::DescriptorType::eCombinedImageSampler,
            vk::ShaderStageFlagBits::eFragment, 0, textures_count)};

    vk::DescriptorSetLayoutCreateInfo layout_info({}, layout_bindings.size(),
                                                  layout_bindings.data());

    m_set_layout =
        m_device_ptr->device().createDescriptorSetLayout(layout_info);
}

void
Model::createDescriptorSet()
{
    auto allocInfo = vk::DescriptorSetAllocateInfo()
                         .setDescriptorPool(m_descriptor_pool)
                         .setDescriptorSetCount(1)
                         .setPSetLayouts(&m_set_layout);

    m_descriptor_set =
        m_device_ptr->device().allocateDescriptorSets(allocInfo).front();
}

void
Model::createDescriptorPool()
{
    std::vector<vk::DescriptorPoolSize> pool_sizes = {
        vk::DescriptorPoolSize()
            .setType(vk::DescriptorType::eCombinedImageSampler)
            .setDescriptorCount(m_texture_count),
        vk::DescriptorPoolSize()
            .setType(vk::DescriptorType::eUniformBuffer)
            .setDescriptorCount(1),
        vk::DescriptorPoolSize()
            .setType(vk::DescriptorType::eStorageBuffer)
            .setDescriptorCount(1)};

    auto pool_info =
        vk::DescriptorPoolCreateInfo().setMaxSets(1).setPoolSizes(pool_sizes);

    m_descriptor_pool = m_device_ptr->device().createDescriptorPool(pool_info);
}

void
Model::updateDescriptorSet()
{
    std::vector<vk::DescriptorImageInfo> imageInfos;
    imageInfos.reserve(m_texture_count);

    for (const auto& texName : {"cat.dds", "eye.dds", "red_eye.dds"})
    {
        imageInfos.emplace_back(m_sampler,
                                m_texture_storage.getTexture(texName),
                                vk::ImageLayout::eShaderReadOnlyOptimal);
    }

    auto descriptorWrite =
        vk::WriteDescriptorSet()
            .setDstSet(m_descriptor_set)
            .setDstBinding(0)
            .setDescriptorType(vk::DescriptorType::eCombinedImageSampler)
            .setImageInfo(imageInfos);

    m_device_ptr->device().updateDescriptorSets(descriptorWrite, nullptr);
}

}; // namespace kusengine
