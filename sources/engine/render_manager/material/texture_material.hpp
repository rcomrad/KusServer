#ifndef TEXTURE_MATERIAL_HPP
#define TEXTURE_MATERIAL_HPP

#include "engine/render_manager/textures/texture_zone.hpp"

#include "material.hpp"

namespace kusengine::render
{
class TextureMaterial : public Material
{
public:
    TextureMaterial(const TextureZone* const texture_zone);

private:
    const TextureZone* m_texture_zone;
};
} // namespace kusengine::render
#endif // TEXTURE_MATERIAL_HPP