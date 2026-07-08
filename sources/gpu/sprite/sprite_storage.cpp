#include "sprite_storage.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/framework/variable/include_me.hpp"

#include "gpu/utils/variable.hpp"
#include "gpu/window/window.hpp"

gpu::sprite::SpriteStorage::SpriteStorage(
    buffer::BaseBuffer&& a_memory,
    vk::UniqueDescriptorPool&& a_descriptor_pool,
    std::unordered_map<std::string, Sprite>&& a_sprites)
    : m_memory(std::move(a_memory)),
      m_descriptor_pool(std::move(a_descriptor_pool))
{
    for (auto&& [name, spr] : a_sprites)
    {
        m_sprites.emplace_back(std::move(spr));
        m_name_to_num.emplace(name, static_cast<int>(m_sprites.size() - 1));
    }
}

void
gpu::sprite::SpriteStorage::resize()
{
    auto size = window::Window::getSize();
    LOG_TRACE("resize all sprites for %d x %d", size.x, size.y);

    for (auto& sprite : m_sprites)
    {
        sprite.resize(size);
    }
}

gpu::sprite::SpriteView
gpu::sprite::SpriteStorage::generateSpriteView(const std::string& a_name) const
{
    auto it = m_name_to_num.find(a_name);
    if (it == m_name_to_num.end())
    {
        THROW("No texture with name '%s'", a_name);
    }
    auto num = it->second;
    return m_sprites.at(num).generateSpriteView(num);
}

const gpu::sprite::Sprite&
gpu::sprite::SpriteStorage::getSprite(int a_sprite_id) const
{
    return m_sprites.at(a_sprite_id);
}
