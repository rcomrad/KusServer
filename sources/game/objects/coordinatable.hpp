#pragma once

#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

namespace game::obj
{

class Coordinatable
{
public:
    Coordinatable(gpu::sprite::SpriteView& a_sprite_view,
                  const gpu::type::Coordinates& a_pos);

    void setPosition(const gpu::type::Coordinates& a_pos);
    void movePosition(const gpu::type::Coordinates& a_delta_pos);
    void repositionForNewWindow(const gpu::type::CoordinateSize& a_old_window,
                                const gpu::type::CoordinateSize& a_new_window);

    const gpu::type::Coordinates& getPosition() const;

    bool isHitBy(const gpu::type::Coordinates& a_pos) const;

private:
    gpu::type::Coordinates m_pos;
    const gpu::type::CoordinateSize m_half_size;

    static gpu::type::Coordinates calcHalfSize(
        gpu::sprite::SpriteView& a_sprite_view);
};

} // namespace game::obj
