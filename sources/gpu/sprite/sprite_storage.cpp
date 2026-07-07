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
      m_descriptor_pool(std::move(a_descriptor_pool)),
      m_sprites(std::move(a_sprites))
{
}

void
gpu::sprite::SpriteStorage::resize()
{
    auto size = window::Window::getSize();
    LOG_TRACE("resize all sprites for %d x %d", size.x, size.y);

    for (auto& [_, texture] : m_sprites)
    {
        texture.resize(size);
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
