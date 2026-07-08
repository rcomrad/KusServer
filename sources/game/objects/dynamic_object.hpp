#pragma once

#include "static_object.hpp"

namespace game::obj
{

class DynamicObject : public StaticObject
{
public:
    DynamicObject(const gpu::sprite::SpriteView& a_sprite_view,
                  int a_pos_x,
                  int a_pos_y);

    void makeConsistentWithWindow(uint32_t a_win_height, uint32_t a_win_width);

private:
    int m_pos_x;
    int m_pos_y;
};

} // namespace game::obj
