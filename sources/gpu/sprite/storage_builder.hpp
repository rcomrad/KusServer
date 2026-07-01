#pragma once

#include <filesystem>
#include <unordered_map>

#include "gpu/command/command_pool.hpp"
#include "gpu/logic/device.hpp"
#include "gpu/logic/queue.hpp"

#include "raw_texture.hpp"
#include "sprite_storage.hpp"

namespace gpu::sprite
{

class StorageBuilder
{
public:
    StorageBuilder(logic::Device& a_device);

    void push(const std::filesystem::path& a_path);
    SpriteStorage collapse(logic::Queue& a_queue,
                           command::CommandPool& a_comm_pool,
                           vk::DescriptorSetLayout a_desc_set_layout);

private:
    logic::Device& m_device;
    std::unordered_map<std::string, RawTexture> m_textures;

    static std::pair<vk::DeviceSize, type::MemoryTypeBits>
    calculateMemoryRequirements(
        logic::Device& a_device,
        const std::unordered_map<std::string, RawTexture>& a_textures);
    static vk::UniqueDescriptorPool createDescriptorPool(
        logic::Device& a_device);
};

} // namespace gpu::sprite
