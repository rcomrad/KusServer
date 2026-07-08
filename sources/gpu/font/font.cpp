#include "font.hpp"

gpu::font::Font::Font(std::unordered_map<char, int>&& a_char_sprites)
{
}

std::vector<gpu::sprite::DrawTask>
gpu::font::Font::writeText(const std::string& a_text, type::Coordinates&& a_pos)
{
    std::vector<sprite::DrawTask> result;

    // TODO: substract pending from a_pos

    for (auto c : a_text)
    {
        // result.emplace_back(m_chars[c]);
    }

    return result;
}
