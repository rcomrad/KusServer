#include "position.hpp"

#include "raw_texture.hpp"
#include "sprite_push_data.hpp"
#include "texture_info.hpp"

gpu::sprite::Position::Position(const RawTexture& a_texture,
                                const TextureInfo& a_info)
    : m_scaler(1, 1),
      m_size(a_texture.getSize().x / a_info.dimensions.x,
             a_texture.getSize().y / a_info.dimensions.y),
      m_hitbox_offset(a_info.hitbox_offset)
{
}

void
gpu::sprite::Position::resize(const type::CoordinateSize& a_win_size)
{
    m_scaler = m_size / a_win_size;
}

// const gpu::type::CoordinateSize&
// gpu::sprite::Position::getSize() const
// {
//     return m_size;
// }

// const gpu::type::Coordinates&
// gpu::sprite::Position::getHitboxOffset() const
// {
//     return m_hitbox_offset;
// }

gpu::sprite::SpriteView
gpu::sprite::Position::generateSpriteView(int a_id) const
{
    return SpriteView(a_id, m_size, m_hitbox_offset);
}

void
gpu::sprite::Position::drawPosition(SpritePushData& a_push) const
{
    a_push.coord_scaler = {m_scaler.x, m_scaler.y};
}
