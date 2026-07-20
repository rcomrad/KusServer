#include "resource_storage.hpp"

gpu::ResourceStorage::ResourceStorage(sprite::SpriteStorage&& a_sprite_storage,
                                      font::FontStorage&& a_font_storage)
    : sprite::SpriteStorage(std::move(a_sprite_storage)),
      font::FontStorage(std::move(a_font_storage))
{
}

const font::FontStorage&
gpu::ResourceStorage::getFontStorage() const
{
    return static_cast<font::FontStorage&>(*this);
}
