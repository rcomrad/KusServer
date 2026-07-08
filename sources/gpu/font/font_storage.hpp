#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "font.hpp"

namespace gpu::font
{

class FontStorage
{
public:
    FontStorage(std::vector<Font>&& a_fonts,
                std::unordered_map<std::string, int>&& a_name_to_num);

    std::vector<sprite::DrawTask> writeText(const std::string& a_text,
                                            const type::Coordinates& a_pos,
                                            int a_font_id);

private:
    std::vector<Font> m_fonts;
    std::unordered_map<std::string, int> m_name_to_num;
};

} // namespace gpu::font
