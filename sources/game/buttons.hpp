#pragma once

#include "gpu/sprite/sprite.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

namespace game
{

class Buttons
{
public:
    Buttons(gpu::sprite::Sprite& a_sprite,
            const gpu::type::Dimensions& a_dem,
            const gpu::type::NDC& a_base_pos,
            const gpu::type::Coordinates& a_offset);

    void update(gpu::type::Coordinates a_coord);
    void resize(const gpu::type::WinSize& a_win_size);

    void pushPresentation(gpu::sprite::SpriteViewArray& a_sprite_views) const;

private:
    gpu::sprite::Sprite& m_sprite;

    gpu::type::Dimensions m_dem;

    gpu::type::NDC m_base_pos;
    gpu::type::NDC m_start_pos;
    gpu::type::NDC m_norm_offset;

    gpu::type::Coordinates m_button_offset;

    mutable int selected = -1;
};

} // namespace game
