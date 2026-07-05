#include "storage_builder.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/utils/paths.hpp"

#include "texture_info.hpp"

gpu::sprite::StorageBuilder::StorageBuilder(logic::Device& a_device)
    : m_device(a_device)
{
}

void
gpu::sprite::StorageBuilder::push(const std::filesystem::path& a_path)
{
    auto file_name = a_path.stem().string();
    LOG_TRACE("Load %s texture", file_name);
    auto file_content = core::FileReader::readBinaryFile(a_path);
    m_textures.emplace(file_name,
                       RawTexture(m_device, std::move(file_content)));
}

gpu::sprite::SpriteStorage
gpu::sprite::StorageBuilder::collapse(logic::Queue& a_queue,
                                      command::CommandPool& a_comm_pool,
                                      vk::DescriptorSetLayout a_desc_set_layout)
{
    SCOPED_TRACE_CREATE("sprite storage")

    auto map_path = KERNEL.getShortcut(IMAGES_DIR, "map.txt");
    auto text_map = KERNEL.readStructMap<TextureInfo>(map_path);

    const auto mem_req = calculateMemoryRequirements(m_device, m_textures);
    buffer::BaseBuffer memory(m_device, mem_req.first, mem_req.second,
                              vk::MemoryPropertyFlagBits::eDeviceLocal);
    buffer::StagingBuffer m_transfer_buff(m_device, 1024 * 1024 * 10);

    std::unordered_map<std::string, Sprite> sprites;
    vk::UniqueDescriptorPool descriptor_pool =
        createDescriptorPool(m_device, m_textures.size());
    for (auto& [name, texture] : m_textures)
    {
        LOG_TRACE("adding %s texture", name);
        texture.writeToBuffer(a_queue, a_comm_pool, memory, m_transfer_buff);

        auto& cur_info = text_map[name];
        sprites.emplace(name, Sprite(m_device, a_desc_set_layout,
                                     *descriptor_pool, texture, cur_info));
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
gpu::sprite::StorageBuilder::createDescriptorPool(logic::Device& a_device,
                                                  int a_set_count)
{
    // TODO: fix a_set_count

    vk::DescriptorPoolSize pool_size;
    pool_size.setType(vk::DescriptorType::eCombinedImageSampler)
        .setDescriptorCount(a_set_count);

    vk::DescriptorPoolCreateInfo pool_info;
    pool_info.setMaxSets(a_set_count)
        .setPoolSizeCount(1)
        .setPPoolSizes(&pool_size);
    return a_device.createDescriptorPoolUnique(pool_info);
}
