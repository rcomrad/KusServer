#include "dynamic_object.hpp"

game::obj::DynamicObject::DynamicObject(
    const gpu::sprite::SpriteView& a_sprite_view,
    int a_pos_x,
    int a_pos_y)
    : StaticObject(a_sprite_view, 0, 0), m_pos_x(a_pos_x), m_pos_y(a_pos_y)
{
}

#include <iostream>
void
game::obj::DynamicObject::makeConsistentWithWindow(uint32_t a_win_height,
                                                   uint32_t a_win_width)
{

    float m_norm_pos_x = static_cast<float>(m_pos_x) / a_win_width * 2;
    float m_norm_pos_y = static_cast<float>(m_pos_y) / a_win_height * 2;
    setPosition(m_norm_pos_x, m_norm_pos_y);
}
