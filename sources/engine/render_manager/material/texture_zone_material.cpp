
#include "texture_zone_material.hpp"

namespace kusengine::render
{
TextureZoneMaterial::TextureZoneMaterial(const TextureZone& texture_zone)
    : Material(Type::TEXTURE_ZONE)
{
    m_texture_zone = texture_zone;
}

void
TextureZoneMaterial::bind(const vk::CommandBuffer& cmd,
                          const vk::PipelineLayout& layout) const
{
    m_texture_zone.m_texture->bind(cmd, layout);
}
} // namespace kusengine::render
