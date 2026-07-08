#include "font_storage.hpp"

gpu::font::FontStorage::FontStorage(
    std::vector<Font>&& a_fonts,
    std::unordered_map<std::string, int>&& a_name_to_num)
    : m_fonts(std::move(a_fonts)), m_name_to_num(a_name_to_num)
{
}

std::vector<gpu::sprite::DrawTask>
gpu::font::FontStorage::writeText(const std::string& a_text,
                                  const type::Coordinates& a_pos,
                                  int a_font_id)
{
    return m_fonts.at(a_font_id).writeText(a_text, a_pos);
}
