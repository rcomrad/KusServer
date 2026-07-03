#include "storage_builder.hpp"

#include "kernel/framework/file_system/file_reader.hpp"
#include "kernel/framework/logger/basic/include_me.hpp"

gpu::sprite::StorageBuilder::StorageBuilder(logic::Device& a_device)
    : m_device(a_device)
{
}

void
gpu::sprite::StorageBuilder::push(const std::filesystem::path& a_path)
{
    auto file_content = core::FileReader::readFile(a_path);
    m_textures.emplace(a_path.stem().string(),
                       RawTexture(m_device, std::move(file_content)));
}

gpu::sprite::SpriteStorage
gpu::sprite::StorageBuilder::collapse(logic::Queue& a_queue,
                                      command::CommandPool& a_comm_pool,
                                      vk::DescriptorSetLayout a_desc_set_layout)
{
    const auto mem_req = calculateMemoryRequirements(m_device, m_textures);
    buffer::BaseBuffer memory(m_device, mem_req.first, mem_req.second,
                              vk::MemoryPropertyFlagBits::eDeviceLocal);
    buffer::StagingBuffer m_transfer_buff(m_device, 1048576);

    std::unordered_map<std::string, Sprite> sprites;
    vk::UniqueDescriptorPool descriptor_pool = createDescriptorPool(m_device);
    for (auto& [name, texture] : m_textures)
    {
        texture.writeToBuffer(a_queue, a_comm_pool, memory, m_transfer_buff);
        sprites.emplace(name, Sprite(m_device, a_desc_set_layout,
                                     *descriptor_pool, texture));
    }

    return SpriteStorage(std::move(memory), std::move(descriptor_pool),
                         std::move(sprites));
}

std::pair<vk::DeviceSize, gpu::type::MemoryTypeBits>
gpu::sprite::StorageBuilder::calculateMemoryRequirements(
    logic::Device& a_device,
    const std::unordered_map<std::string, RawTexture>& a_textures)
{
    vk::DeviceSize total_size          = 0;
    type::MemoryTypeBits total_filters = ~0;
    for (auto& [name, texture] : a_textures)
    {
        const auto mem_req = texture.getMemReq(a_device);
        total_size += mem_req.size;
        total_filters &= mem_req.memoryTypeBits;

        if (!total_filters)
        {
            THROW("Can't store all images in one buffer: no sutable memory "
                  "type after adding '%s' image",
                  name);
        }
    }
    return {total_size, total_filters};
}

vk::UniqueDescriptorPool
gpu::sprite::StorageBuilder::createDescriptorPool(logic::Device& a_device)
{
    vk::DescriptorPoolSize pool_size;
    pool_size.setType(vk::DescriptorType::eCombinedImageSampler)
        .setDescriptorCount(1);

    vk::DescriptorPoolCreateInfo pool_info;
    pool_info.setMaxSets(1).setPoolSizeCount(1).setPPoolSizes(&pool_size);
    return a_device.createDescriptorPoolUnique(pool_info);
}
