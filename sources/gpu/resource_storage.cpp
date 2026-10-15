#include "resource_storage.hpp"

gpu::ResourceStorage::ResourceStorage(sprite::SpriteStorage&& a_sprite_storage,
                                      font::FontStorage&& a_font_storage)
    : sprite::SpriteStorage(std::move(a_sprite_storage)),
      font::FontStorage(std::move(a_font_storage))
{
}

const gpu::font::FontStorage&
gpu::ResourceStorage::getFontStorage() const
{
    return static_cast<const gpu::font::FontStorage&>(*this);
}

// std::unordered_map<std::string, gpu::sprite::SpriteView>
// gpu::ResourceStorage::generateSpriteViews(
//     std::vector<std::string> const& a_names)
// {
//     std::unordered_map<std::string, sprite::SpriteView> result;
//     for (auto const& name : a_names)
//     {
//         result.emplace(name, generateSpriteView(name));
//     }
//     return result;
// }
