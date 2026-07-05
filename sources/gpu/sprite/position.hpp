#pragma once

#include "kernel/utility/type/declaration/pair.hpp"

#include "gpu/utils/typedef.hpp"

#include "raw_texture.hpp"
#include "sprite_push_data.hpp"
#include "texture_info.hpp"

namespace gpu::sprite
{
class Position
{
    using Scale = core::Pair<float>;

public:
    void resize(const type::WinSize& a_win_size);
    const type::SpriteSize& getSize() const;
    const type::SpriteSize& getHitboxOffset() const;

protected:
    Position(const RawTexture& a_texture, const TextureInfo& a_info);

    void drawPosition(SpritePushData& a_push);

private:
    type::SpriteSize m_size;
    type::Coordinates m_hitbox_offset;
    Scale m_scaler;
};

} // namespace gpu::sprite
