#include "textable.hpp"

game::Textable::Textable(gpu::sprite::SpriteView& a_sprite_view,
                         const gpu::type::Coordinates& a_pos)
    : Drawable(a_sprite_view, a_pos), m_sprite_id(a_sprite_view.id)
{
}

void
game::GameObject::setText(const std::string& a_text)
{
    m_text = a_text;
}

void
game::GameObject::setTextPositionOffset(const gpu::type::Coordinates& a_offset)
{
    m_text_offset = a_offset;
}

void
game::GameObject::getPresentation(
    std::vector<gpu::sprite::DrawTask>& a_draw_tasks) const
{
    a_draw_tasks.emplace_back(getObjectPresentation());
    a_draw_tasks.emplace_back(m_sprite_id, getPosition());
}
