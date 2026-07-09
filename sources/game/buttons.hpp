#pragma once

#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

namespace game
{

class Buttons
{
public:
    Buttons(const gpu::sprite::SpriteView& a_sprite_view,
            const gpu::type::Dimensions& a_dem,
            const gpu::type::NDC& a_base_pos,
            const gpu::type::Coordinates& a_offset);

    void update(gpu::type::Coordinates a_coord);
    void resize(const gpu::type::CoordinateSize& a_win_size);

    void pushPresentation(gpu::sprite::DrawTaskArray& a_draw_tasks) const;

private:
    gpu::sprite::SpriteView m_sprite_view;

    gpu::type::Dimensions m_dem;

    gpu::type::NDC m_base_pos;
    gpu::type::NDC m_start_pos;
    gpu::type::NDC m_norm_offset;

    gpu::type::Coordinates m_button_offset;

    mutable int selected = -1;
};

} // namespace game
