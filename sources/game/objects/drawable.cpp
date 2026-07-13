#include "drawable.hpp"

game::Drawable::Drawable(gpu::sprite::SpriteView& a_sprite_view,
                         const gpu::type::Coordinates& a_pos)
    : Coordinatable(a_pos), m_sprite_id(a_sprite_view.id)
{
}

void
game::GameObject::getObjectPresentation(
    std::vector<gpu::sprite::DrawTask>& a_draw_tasks) const
{
    return gpu::sprite::DrawTask(m_sprite_id, getPosition());
}
