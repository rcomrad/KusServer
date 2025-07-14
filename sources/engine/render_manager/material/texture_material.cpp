
#include "texture_material.hpp"

namespace kusengine::render
{
TextureMaterial::TextureMaterial(const TextureZone* const texture_zone)
    : Material(Type::TEXTURE), m_texture_zone(texture_zone)
{
}
} // namespace kusengine::render
