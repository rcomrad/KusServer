#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "gpu/sprite/draw_task.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/utils/typedef.hpp"

namespace gpu::font
{

class Font
{
public:
    Font(std::unordered_map<char, sprite::SpriteView>&& a_char_sprites);

    void writeText(const std::string& a_text,
                   const type::Coordinates& a_pos,
                   std::vector<sprite::DrawTask>& a_out);

private:
    std::unordered_map<char, sprite::SpriteView> m_char_sprites;
};

} // namespace gpu::font
