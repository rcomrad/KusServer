#include "buttons.hpp"

#include "gpu/window/window.hpp"

game::Buttons::Buttons(const gpu::sprite::SpriteView& a_sprite_view,
                       const gpu::type::Dimensions& a_dem,
                       const gpu::type::NDC& a_base_pos,
                       const gpu::type::Coordinates& a_offset)
    : m_sprite_view(a_sprite_view),
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
    auto win_size    = gpu::window::Window::getSize();
    auto sprite_size = m_sprite_view.size / 2 - m_sprite_view.hitbox_offset;

    selected = -1;
    int cnt  = 0;

    for (int i = 0; i < m_dem.x; ++i)
    {
        for (int j = 0; j < m_dem.y; ++j)
        {
            auto cur =
                m_start_pos + m_norm_offset * gpu::type::Dimensions(i, j);
            cur += 1;
            cur /= 2;

            auto centr = win_size * cur;

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
game::Buttons::resize(const gpu::type::CoordinateSize& a_win_size)
{
    auto size     = m_sprite_view.size;
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
game::Buttons::pushPresentation(gpu::sprite::DrawTaskArray& a_draw_tasks) const
{
    for (int i = 0; i < m_dem.x; ++i)
    {
        for (int j = 0; j < m_dem.y; ++j)
        {
            a_draw_tasks.emplace_back(
                m_sprite_view,
                m_start_pos + m_norm_offset * gpu::type::Dimensions(i, j),
                selected == j ? 1 : 0);
        }
    }

    std::cout << selected << std::endl;
}
