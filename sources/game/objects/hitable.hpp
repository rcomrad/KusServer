#pragma once

#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

namespace game::obj
{

class ObjectInfo;

class Hitable
{
public:
    Hitable(const ObjectInfo& a_info);
    Hitable(Hitable&& a_other) noexcept = default;

    bool isHitBy(const gpu::type::Coordinates& a_pos) const;

private:
    const gpu::type::CoordinateSize m_half_size;

    static gpu::type::Coordinates calcHalfSize(
        const std::optional<gpu::sprite::SpriteView>& a_sprite_view);
};

} // namespace game::obj
