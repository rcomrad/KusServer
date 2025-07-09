#include "engine/render_manager/textures/texture_zone.hpp"

#include "material.hpp"

namespace kusengine::render
{
class DefaultMaterial : public Material
{
public:
    DefaultMaterial();

private:
    const TextureZone* const m_texture;
};
} // namespace kusengine::render
