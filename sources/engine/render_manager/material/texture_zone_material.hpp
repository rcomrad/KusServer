#ifndef TEXTURE_MATERIAL_HPP
#define TEXTURE_MATERIAL_HPP

#include "engine/render_manager/textures/texture_zone.hpp"

#include "material_not_full.hpp"

namespace kusengine::render
{
class TextureZoneMaterial : public Material
{
public:
    TextureZoneMaterial(const TextureZone& texture_zone);

    void bind(const vk::CommandBuffer& cmd,
              const vk::PipelineLayout& layout) const override;

    template <typename Vertex_t>
    void upgradeVertsConcreateImpl(std::vector<Vertex_t>& verts) const
    {
        for (int i = 0; i < verts.size(); ++i)
        {
            glm::vec2 uv = verts[i].getUV();

            uv *= m_texture_zone.m_scale;
            uv += m_texture_zone.m_offset;

            verts[i].setUV(uv);
        }
    };

private:
    TextureZone m_texture_zone;
};
} // namespace kusengine::render
#endif // TEXTURE_MATERIAL_HPP
