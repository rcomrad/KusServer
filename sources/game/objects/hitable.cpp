#include "hitable.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "coordinatable.hpp"
#include "object_info.hpp"

game::obj::Hitable::Hitable(const ObjectInfo& a_info)
    : Coordinatable(a_info), m_half_size(calcHalfSize(a_info.sprite_view))
{
}

bool
game::obj::Hitable::isHitBy(const gpu::type::Coordinates& a_pos) const
{
    const auto& pos = getPosition();
    return a_pos.inside(pos - m_half_size) && (pos + m_half_size).inside(a_pos);
}

gpu::type::Coordinates
game::obj::Hitable::calcHalfSize(
    const std::optional<gpu::sprite::SpriteView>& a_sprite_view)
{
    if (!a_sprite_view.has_value())
    {
        THROW("Requers texture for hitable property");
    }

    gpu::type::Coordinates result = a_sprite_view.value().size;
    result /= 2;
    result += a_sprite_view.value().hitbox_offset;
    return result;
}
