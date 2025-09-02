#include "ubo_storage_resource_storage.hpp"

namespace kusengine::render
{

UboStorageResorceStorage::UboStorageResorceStorage(
    const kusengine::render::DescriptorManager& desc_manager)
    : ResourceStorage(desc_manager, DescriptorSetLayoutType::UBO_x_STORAGE)
{
}

void
UboStorageResorceStorage::updateBuffers(const updBuffersDataArgs& m_data)
{
    m_uniform_buffer.setData(&m_data.ubo->camera_matrix, sizeof(m_data.ubo));
    m_storage_buffer.setData(m_data.storage->data(), m_data.storage->size());

    writeDescriptorSet();
}

void
UboStorageResorceStorage::writeDescriptorSet() const noexcept
{
    // UBO

    vk::DescriptorBufferInfo ubo_buffer_info{};
    ubo_buffer_info.buffer = m_uniform_buffer.buffer();
    ubo_buffer_info.offset = 0;
    ubo_buffer_info.range  = m_uniform_buffer.byteSize();

    vk::WriteDescriptorSet ubo_descriptor_write;
    ubo_descriptor_write.dstSet          = m_descriptor_sets[0];
    ubo_descriptor_write.dstBinding      = 0;
    ubo_descriptor_write.dstArrayElement = 0;
    ubo_descriptor_write.descriptorType  = vk::DescriptorType::eUniformBuffer;
    ubo_descriptor_write.descriptorCount = 1;
    ubo_descriptor_write.pBufferInfo     = &ubo_buffer_info;

    LOGICAL_DEVICE_INSTANCE.updateDescriptorSets(1, &ubo_descriptor_write, 0,
                                                 nullptr);

    // storage buffer

    vk::DescriptorBufferInfo st_buffer_info{};
    st_buffer_info.buffer = m_storage_buffer.buffer();
    st_buffer_info.offset = 0;
    st_buffer_info.range  = m_storage_buffer.byteSize();

    vk::WriteDescriptorSet stb_descriptor_write;
    stb_descriptor_write.dstSet          = m_descriptor_sets[0];
    stb_descriptor_write.dstBinding      = 1;
    stb_descriptor_write.dstArrayElement = 0;
    stb_descriptor_write.descriptorType  = vk::DescriptorType::eStorageBuffer;
    stb_descriptor_write.descriptorCount = 1;
    stb_descriptor_write.pBufferInfo     = &st_buffer_info;

    LOGICAL_DEVICE_INSTANCE.updateDescriptorSets(1, &stb_descriptor_write, 0,
                                                 nullptr);
}
} // namespace kusengine::render
