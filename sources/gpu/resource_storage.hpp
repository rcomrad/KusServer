#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"

#include "font/font_storage.hpp"
#include "sprite/sprite_storage.hpp"
#include "sprite/sprite_view.hpp"

namespace gpu
{

class ResourceStorage : public sprite::SpriteStorage, public font::FontStorage
{
public:
    ResourceStorage(sprite::SpriteStorage&& a_sprite_storage,
                    font::FontStorage&& a_font_storage);
    HOLY_TRINITY_ONLY_MOVE(ResourceStorage);

    const font::FontStorage& getFontStorage() const;

    // std::unordered_map<std::string, sprite::SpriteView> generateSpriteViews(
    //     std::vector<std::string> const& a_names);
};

} // namespace gpu
