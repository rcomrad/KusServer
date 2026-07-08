#pragma once

#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite_view.hpp"

namespace game::obj
{

class StaticObject
{
public:
    StaticObject(const gpu::sprite::SpriteView& a_sprite_view,
                 float a_pos_x,
                 float a_pos_y);

    gpu::sprite::DrawTask getPresentation() const;

protected:
    void setPosition(float a_pos_x, float a_pos_y);

private:
    gpu::sprite::SpriteView m_sprite_view;

    float m_pos_x;
    float m_pos_y;
};

} // namespace game::obj
