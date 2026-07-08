#include "font.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

gpu::font::Font::Font(
    std::unordered_map<char, sprite::SpriteView>&& a_char_sprites)
    : m_char_sprites(std::move(a_char_sprites))
{
}

std::vector<gpu::sprite::DrawTask>
gpu::font::Font::writeText(const std::string& a_text,
                           const type::Coordinates& a_pos)
{
    std::vector<sprite::DrawTask> result;

    // TODO: substract pending from a_pos

    for (int i = 0; i < a_text.size(); ++i)
    {
        auto c = a_text[i];
        // TODO: MCVS bug - try to copy:
        // const sprite::SpriteView& cc = m_char_sprites[c];

        auto it = m_char_sprites.find(c);
        if (it == m_char_sprites.end())
        {
            THROW("No such character %d", c);
        }

        result.emplace_back(sprite::DrawTask(
            it->second, type::toNDC(a_pos + type::Coordinates(30, 0) * i)));
    }

    return result;
}
