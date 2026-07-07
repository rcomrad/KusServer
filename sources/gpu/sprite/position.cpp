#include "position.hpp"

gpu::sprite::Position::Position(const RawTexture& a_texture,
                                const TextureInfo& a_info)
    : m_hitbox_offset(a_info.hitbox_offset)
{
    m_size.assign(a_texture.getSize() / a_info.dimensions);
}

void
gpu::sprite::Position::resize(const type::WinSize& a_win_size)
{
    m_scaler = m_size / a_win_size;

    // std::cout << "W: " << a_win_width << " " << m_width << " " << m_scaler_y
    //           << std::endl;
    // std::cout << "H: " << a_win_height << " " << m_height << " " <<
    // m_scaler_x
    //           << std::endl;

    // std::cout << a_win_height << " " << a_win_width << std::endl;
    // std::cout << m_scaler_x << " " << m_scaler_y << std::endl;
}

const gpu::type::SpriteSize&
gpu::sprite::Position::getSize() const
{
    return m_size;
}

const gpu::type::Coordinates&
gpu::sprite::Position::getHitboxOffset() const
{
    return m_hitbox_offset;
}

void
gpu::sprite::Position::drawPosition(SpritePushData& a_push)
{
    a_push.coord_scaler = {m_scaler.x, m_scaler.y};
}
