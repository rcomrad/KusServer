#pragma once

#include <string>
#include <vector>

#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

#include "coordinatable.hpp"

namespace game::obj
{

class Drawable : public Coordinatable
{
public:
    Drawable(gpu::sprite::SpriteView& a_sprite_view,
             const gpu::type::Coordinates& a_pos);

    gpu::sprite::DrawTask getObjectPresentation() const;

private:
    int m_sprite_id;
};

} // namespace game::obj
