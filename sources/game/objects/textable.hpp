#pragma once

#include <string>
#include <vector>

#include "gpu/font/font.hpp"
#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

#include "drawable.hpp"

namespace game::obj
{

class Textable : public Drawable
{
public:
    Textable(gpu::sprite::SpriteView& a_sprite_view,
             const gpu::type::Coordinates& a_pos);

    void setText(const std::string& a_text);
    void setTextPositionOffset(const gpu::type::Coordinates& a_offset);

    void addPresentation(
        // give gpu manager as argument (sprite storage & font storage)
        std::vector<gpu::sprite::DrawTask>& a_draw_tasks) const;

private:
    std::string m_text;
    gpu::type::Coordinates m_text_offset;

    // store font id
};

} // namespace game::obj
