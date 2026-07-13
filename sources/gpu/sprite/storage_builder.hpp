#pragma once

#include <filesystem>
#include <unordered_map>

#include "raw_texture.hpp"
#include "sprite_storage.hpp"

namespace gpu
{

namespace logic
{
class Device;
class Queue;
} // namespace logic
namespace command
{
class CommandPool;
}

namespace sprite
{

class SpriteStorageBuilder
{
public:
    SpriteStorageBuilder(logic::Device& a_device);

    void push(const std::string& a_name, PixelArray&& a_pixel_array);
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
        logic::Device& a_device,
        int a_set_count);
};

} // namespace sprite

} // namespace gpu
