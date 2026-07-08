#include "font_storage_builder.hpp"

#include "kernel/framework/include_me.hpp"

#include <unordered_map>

#include "gpu/sprite/sprite_storage.hpp"
#include "gpu/sprite/sprite_view.hpp"
#include "gpu/sprite/storage_builder.hpp"
#include "gpu/utils/paths.hpp"

#include "face_instance.hpp"
#include "font_info.hpp"
#include "freetype_instance.hpp"

gpu::font::FontStorageBuilder::FontStorageBuilder(
    sprite::StorageBuilder& a_builder)
    : m_builder(a_builder)
{
}

void
gpu::font::FontStorageBuilder::push(const std::string& a_name,
                                    const FontInfo& a_info,
                                    const std::filesystem::path& a_path)
{
    if (m_nicknames.count(a_name))
    {
        THROW("Font '%s' already exist", a_name);
    }
    m_nicknames.emplace(a_name);

    gpu::font::FreeTypeInstance lib;
    gpu::font::FaceInstance face(lib, a_path.string());
    face.setPixelSize(a_info.size);

    for (char c = CHAR_FROM; c < CHAR_TO; ++c)
    {
        auto cur_name = genCharName(a_name, c);
        auto glyth    = face.renderGlyph(c);
        m_builder.push(cur_name, glyth.createPixelArray(a_info.color));
    }
}

gpu::font::FontStorage
gpu::font::FontStorageBuilder::collapse(const sprite::SpriteStorage& a_storage)
{

    std::vector<Font> fonts;
    std::unordered_map<std::string, int> name_to_num;

    for (auto& name : m_nicknames)
    {
        std::unordered_map<char, sprite::SpriteView> char_sprites;
        for (char c = CHAR_FROM; c < CHAR_TO; ++c)
        {
            auto cur_name    = genCharName(name, c);
            auto sprite_view = a_storage.generateSpriteView(cur_name);
            char_sprites.emplace(c, std::move(sprite_view));
        }

        fonts.emplace_back(std::move(char_sprites));
        name_to_num.emplace(name, static_cast<int>(fonts.size() - 1));
    }

    return gpu::font::FontStorage(std::move(fonts), std::move(name_to_num));
}

std::string
gpu::font::FontStorageBuilder::genCharName(const std::string& a_name,
                                           int a_char)
{
    return a_name + "_" + std::to_string(a_char);
}
