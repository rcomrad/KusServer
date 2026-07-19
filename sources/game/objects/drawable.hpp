#pragma once

#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

namespace game::obj
{

class ObjectInfo;

class Drawable
{
public:
    Drawable(const ObjectInfo& a_info);
    Drawable(Drawable&& a_other) noexcept = default;

    gpu::sprite::DrawTask getObjectPresentation() const;

private:
    int m_sprite_id;
};

} // namespace game::obj
