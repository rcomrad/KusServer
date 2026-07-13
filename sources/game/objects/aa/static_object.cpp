#include "static_object.hpp"

#include "gpu/utils/typedef.hpp"

game::obj::StaticObject::StaticObject(
    const gpu::sprite::SpriteView& a_sprite_view,
    float a_pos_x,
    float a_pos_y)
    : m_sprite_view(a_sprite_view)
{
    setPosition(a_pos_x, a_pos_y);
}

void
game::obj::StaticObject::setPosition(float a_pos_x, float a_pos_y)
{
    m_pos_x = a_pos_x;
    m_pos_y = a_pos_y;
}

gpu::sprite::DrawTask
game::obj::StaticObject::getPresentation() const
{
    return gpu::sprite::DrawTask(m_sprite_view, gpu::type::NDC(0, 0));
}
