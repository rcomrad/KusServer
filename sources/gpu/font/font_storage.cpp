#include "font_storage.hpp"

gpu::font::FontStorage::FontStorage(
    std::vector<Font>&& a_fonts,
    std::unordered_map<std::string, int>&& a_name_to_num)
    : m_fonts(std::move(a_fonts)), m_name_to_num(a_name_to_num)
{
}

void
gpu::font::FontStorage::writeText(const std::string& a_text,
                                  const type::Coordinates& a_pos,
                                  int a_font_id,
                                  std::vector<sprite::DrawTask>& a_out)
{
    return m_fonts.at(a_font_id).writeText(a_text, a_pos, a_out);
}

int
gpu::font::FontStorage::getFontId(const std::string& a_font_name) const
{
    auto it = m_name_to_num.find(a_font_name);
    if (it == m_name_to_num.end())
    {
        THROW("No font with nickname %s", a_font_name);
    }
}
