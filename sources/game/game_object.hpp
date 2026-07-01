#pragma once

#include "gpu/sprite/sprite.hpp"
#include "gpu/sprite/sprite_view.hpp"

namespace game
{

class GameObject
{
public:
    GameObject(gpu::sprite::Sprite& a_sprite, int a_pos_x, int a_pos_y);

    void update(uint32_t a_win_height, uint32_t a_win_width);

    gpu::sprite::SpriteView getPresentation() const;

private:
    gpu::sprite::Sprite& m_sprite;

    int m_pos_x;
    int m_pos_y;

    float m_norm_pos_x;
    float m_norm_pos_y;
};

} // namespace game
