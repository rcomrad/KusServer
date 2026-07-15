#include "font/font_storage.hpp"
#include "sprite/sprite_storage.hpp"

namespace gpu
{

class ResourceStorage : public sprite::SpriteStorage, public font::FontStorage
{
public:
    ResourceStorage(sprite::SpriteStorage&& a_sprite_storage,
                    public font::FontStorage&& a_font_storage);
};

} // namespace gpu
