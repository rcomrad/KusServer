#pragma once

#include <vulkan/vulkan.hpp>

#include <unordered_map>

#include "gpu/buffers/base_buffer.hpp"

#include "sprite.hpp"

namespace gpu::sprite
{

class SpriteStorage
{
public:
    SpriteStorage(buffer::BaseBuffer&& a_memory,
                  vk::UniqueDescriptorPool&& a_descriptor_pool,
                  std::unordered_map<std::string, Sprite>&& a_sprites);

    void resize();
    Sprite& get(const std::string& a_name);

private:
    buffer::BaseBuffer m_memory;
    vk::UniqueDescriptorPool m_descriptor_pool;
    std::unordered_map<std::string, Sprite> m_sprites;
};

} // namespace gpu::sprite
