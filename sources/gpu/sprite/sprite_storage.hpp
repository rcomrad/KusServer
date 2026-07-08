#pragma once

#include <vulkan/vulkan.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#include "gpu/buffers/base_buffer.hpp"

#include "sprite.hpp"
#include "sprite_view.hpp"

namespace gpu
{

namespace sprite
{

class SpriteStorage
{
public:
    SpriteStorage(buffer::BaseBuffer&& a_memory,
                  vk::UniqueDescriptorPool&& a_descriptor_pool,
                  std::unordered_map<std::string, Sprite>&& a_sprites);

    void resize();

    SpriteView generateSpriteView(const std::string& a_name) const;
    const Sprite& getSprite(int a_sprite_id) const;

private:
    buffer::BaseBuffer m_memory;
    vk::UniqueDescriptorPool m_descriptor_pool;

    std::vector<Sprite> m_sprites;
    std::unordered_map<std::string, int> m_name_to_num;
};

} // namespace sprite

} // namespace gpu
