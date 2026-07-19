#include "hitable.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "coordinatable.hpp"
#include "object_info.hpp"

game::Coordinatable::Coordinatable(const ObjectInfo& a_info)
    : m_half_size(calcHalfSize(a_info.sprite_view))
{
}

bool
game::Coordinatable::isHitBy(const gpu::type::Coordinates& a_pos) const
{
    const auto& pos = dynamic_cast<Coordinatable&>(*this).getPosition();
    return a_pos.inside(pos - m_half_size) && (pos + m_half_size).inside(a_pos);
}

gpu::type::Coordinates
game::Coordinatable::calcHalfSize(
    const std::optional<gpu::sprite::SpriteView>& a_sprite_view)
{
    if (!a_sprite_view.has_value())
    {
        THROW("Requers texture for hitable property");
    }

    gpu::type::Coordinates result = a_sprite_view.size();
    result /= 2;
    result += a_sprite_view.hitbox_offset;
    return result;
}
