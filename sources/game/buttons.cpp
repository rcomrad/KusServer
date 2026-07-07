#include "buttons.hpp"

#include "gpu/window/window.hpp"

game::Buttons::Buttons(gpu::sprite::Sprite& a_sprite,
                       const gpu::type::Dimensions& a_dem,
                       const gpu::type::NDC& a_base_pos,
                       const gpu::type::Coordinates& a_offset)
    : m_sprite(a_sprite),
      m_dem(a_dem),
      m_base_pos(a_base_pos),
      m_button_offset(a_offset)
{
}

#include <iostream>

void
game::Buttons::update(gpu::type::Coordinates a_coord)
{
    // TODO: maybe we need to use logical coordinates
    auto win_size = gpu::window::Window::getSize();

    auto tmp1 = m_sprite.getSize();
    auto tmp2 = m_sprite.getSize() / 2;
    auto tmp3 = m_sprite.getHitboxOffset();

    auto sprite_size = m_sprite.getSize() / 2 - m_sprite.getHitboxOffset();

    selected = -1;
    int cnt  = 0;

    for (int i = 0; i < m_dem.x; ++i)
    {
        for (int j = 0; j < m_dem.y; ++j)
        {
            auto tmp4 = m_norm_offset * gpu::type::Dimensions(i, j);

            auto cur =
                m_start_pos + m_norm_offset * gpu::type::Dimensions(i, j);
            cur += 1;
            cur /= 2;

            auto centr = win_size * cur;

            auto tmp5 = centr - sprite_size;
            auto tmp6 = a_coord.inside(centr - sprite_size);
            auto tmp7 = centr + sprite_size;
            auto tmp8 = (centr + sprite_size).inside(a_coord);

            if (a_coord.inside(centr - sprite_size) &&
                (centr + sprite_size).inside(a_coord))
            {
                std::cout << "HIT! " << cnt << std::endl;
                selected = cnt;
            }

            cnt++;
        }
    }
}

void
game::Buttons::resize(const gpu::type::WinSize& a_win_size)
{
    auto size     = m_sprite.getSize();
    m_norm_offset = (size + m_button_offset) / (a_win_size) * 2;

    gpu::type::Dimensions half_dem(m_dem.x / 2, m_dem.y / 2);
    m_start_pos = m_base_pos - m_norm_offset * half_dem;

    if (!(m_dem.x & 1))
    {
        m_start_pos.x += m_norm_offset.x / 2;
    }
    if (!(m_dem.y & 1))
    {
        m_start_pos.y += m_norm_offset.y / 2;
    }
}

void
game::Buttons::pushPresentation(
    gpu::sprite::SpriteViewArray& a_sprite_views) const
{
    for (int i = 0; i < m_dem.x; ++i)
    {
        for (int j = 0; j < m_dem.y; ++j)
        {
            a_sprite_views.emplace_back(
                m_sprite,
                m_start_pos + m_norm_offset * gpu::type::Dimensions(i, j));
        }
    }

    if (selected > -1)
    {
        a_sprite_views.at(selected).selectAnimation(1);
        // selected = -1;
    }
}
