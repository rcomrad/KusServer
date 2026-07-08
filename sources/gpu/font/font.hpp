#pragma once

#include <unordered_map>
#include <vector>

#include "gpu/sprite/draw_task.hpp"
#include "gpu/utils/typedef.hpp"

namespace gpu::font
{

class Font
{
public:
    Font(std::unordered_map<char, int>&& a_char_sprites);

    std::vector<sprite::DrawTask> writeText(const std::string& a_text,
                                            type::Coordinates&& a_pos);

private:
    std::unordered_map<char, int> m_char_sprites;
};

} // namespace gpu::font
