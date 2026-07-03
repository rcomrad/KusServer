#include "sprite_storage.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

#include "gpu/utils/variable.hpp"

gpu::sprite::SpriteStorage::SpriteStorage(
    buffer::BaseBuffer&& a_memory,
    vk::UniqueDescriptorPool&& a_descriptor_pool,
    std::unordered_map<std::string, Sprite>&& a_sprites)
    : m_memory(std::move(a_memory)),
      m_descriptor_pool(std::move(a_descriptor_pool)),
      m_sprites(std::move(a_sprites))
{
}

void
gpu::sprite::SpriteStorage::resize()
{
    core::IntVar height_var(VAR_NAME_FRAME_WIDTH);
    core::IntVar width_var(VAR_NAME_FRAME_HEIGHT);

    auto height = height_var.get();
    auto width  = width_var.get();

    for (auto& [_, texture] : m_sprites)
    {
        texture.resize(height, width);
    }
}

gpu::sprite::Sprite&
gpu::sprite::SpriteStorage::get(const std::string& a_name)
{
    auto it = m_sprites.find(a_name);
    if (it == m_sprites.end())
    {
        THROW("No texture with name '%s'", a_name);
    }
    return it->second;
}
