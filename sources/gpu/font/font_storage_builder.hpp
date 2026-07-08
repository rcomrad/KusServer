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
class StorageBuilder;
} // namespace sprite

namespace font
{

class FontInfo;

class FontStorageBuilder
{
public:
    FontStorageBuilder(sprite::StorageBuilder& a_builder);

    void push(const std::string& a_name,
              const FontInfo& a_info,
              const std::filesystem::path& a_path);

    FontStorage collapse(sprite::SpriteStorage& builder);

private:
    static inline const int CHAR_FROM = 33;
    static inline const int CHAR_TO   = 127;

    sprite::StorageBuilder& m_builder;
    std::unordered_set<std::string> m_nicknames;

    static std::string genCharName(const std::string& a_name, int a_char);
};

} // namespace font

} // namespace gpu
