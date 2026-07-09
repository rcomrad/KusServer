#pragma once

#include "gpu/utils/typedef.hpp"

namespace gpu::sprite
{

struct SpriteView
{
    const int sprite_id;
    const type::CoordinateSize size;
    const type::Coordinates hitbox_offset;
};

} // namespace gpu::sprite
