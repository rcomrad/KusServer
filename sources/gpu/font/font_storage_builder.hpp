#pragma once

#include <filesystem>
#include <string>
#include <unordered_set>

#include "font_storage.hpp"

namespace gpu
{

namespace sprite
{
class SpriteStorage;
class SpriteStorageBuilder;
} // namespace sprite

namespace font
{

class FontInfo;

class FontStorageBuilder
{
public:
    FontStorageBuilder(sprite::SpriteStorageBuilder& a_builder);

    void push(const std::string& a_name,
              const FontInfo& a_info,
              const std::filesystem::path& a_path);

    FontStorage collapse(const sprite::SpriteStorage& a_storage);

private:
    static inline const int CHAR_FROM = 33;
    static inline const int CHAR_TO   = 127;

    sprite::SpriteStorageBuilder& m_builder;
    std::unordered_set<std::string> m_nicknames;

    static std::string genCharName(const std::string& a_name, int a_char);
};

} // namespace font

} // namespace gpu
