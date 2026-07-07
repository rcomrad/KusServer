#include "static_object.hpp"

#include "gpu/utils/typedef.hpp"

game::obj::StaticObject::StaticObject(gpu::sprite::Sprite& a_sprite,
                                      float a_pos_x,
                                      float a_pos_y)
    : m_sprite(a_sprite)
{
    setPosition(a_pos_x, a_pos_y);
}

void
game::obj::StaticObject::setPosition(float a_pos_x, float a_pos_y)
{
    m_pos_x = a_pos_x;
    m_pos_y = a_pos_y;
}

gpu::sprite::SpriteView
game::obj::StaticObject::getPresentation() const
{
    return gpu::sprite::SpriteView(m_sprite, gpu::type::NDC(0, 0));
}
