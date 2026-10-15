#pragma once

#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

#include "coordinatable.hpp"

namespace game::obj
{

struct ObjectInfo;

class Drawable : virtual public Coordinatable
{
public:
    Drawable(const ObjectInfo& a_info);
    Drawable(Drawable&& a_other) noexcept = default;

    gpu::sprite::DrawTask getObjectPresentation() const;

private:
    int m_sprite_id;
};

} // namespace game::obj
