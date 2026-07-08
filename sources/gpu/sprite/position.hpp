#pragma once

#include "kernel/utility/type/declaration/pair.hpp"

#include "gpu/utils/typedef.hpp"

#include "sprite_view.hpp"

namespace gpu
{

namespace sprite
{

class RawTexture;
class SpritePushData;
class TextureInfo;

class Position
{
    using Scale = core::Pair<float>;

public:
    void resize(const type::CoordinateSize& a_win_size);
    // const type::CoordinateSize& getSize() const;
    // const type::CoordinateSize& getHitboxOffset() const;

    SpriteView generateSpriteView(int a_id) const;

protected:
    Position(const RawTexture& a_texture, const TextureInfo& a_info);

    void drawPosition(SpritePushData& a_push) const;

private:
    Scale m_scaler;
    const type::CoordinateSize m_size;
    const type::Coordinates m_hitbox_offset;
};

} // namespace sprite

} // namespace gpu
