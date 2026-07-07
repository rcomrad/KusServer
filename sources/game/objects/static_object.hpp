#pragma once

#include "gpu/sprite/sprite.hpp"
#include "gpu/sprite/sprite_view.hpp"

namespace game::obj
{

class StaticObject
{
public:
    StaticObject(gpu::sprite::Sprite& a_sprite, float a_pos_x, float a_pos_y);

    gpu::sprite::SpriteView getPresentation() const;

protected:
    void setPosition(float a_pos_x, float a_pos_y);

private:
    gpu::sprite::Sprite& m_sprite;

    float m_pos_x;
    float m_pos_y;
};

} // namespace game::obj
