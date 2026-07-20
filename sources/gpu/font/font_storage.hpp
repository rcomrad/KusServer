#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"

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
    HOLY_TRINITY_ONLY_MOVE(FontStorage);

    void writeText(const std::string& a_text,
                   const type::Coordinates& a_pos,
                   int a_font_id,
                   std::vector<sprite::DrawTask>& a_out);

    int getFontId(const std::string& a_font_name) const;

private:
    std::vector<Font> m_fonts;
    std::unordered_map<std::string, int> m_name_to_num;
};

} // namespace gpu::font
