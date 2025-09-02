#ifndef MATERIAL_NOT_FULL_HPP
#define MATERIAL_NOT_FULL_HPP

#include <vulkan/vulkan.hpp>

#include <string>

namespace kusengine::render
{
class Material
{
public:
    virtual ~Material() = default;

    template <typename Vertex_t>
    void upgradeVerts(std::vector<Vertex_t>& verts) const;

    enum class Type
    {
        TEXTURE_ZONE
    };
    Material(Type t);

    virtual void bind(const vk::CommandBuffer& cmd,
                      const vk::PipelineLayout& layout) const = 0;

    Type getType() const noexcept;

private:
    template <typename Vertex_t, typename Material_t>
    void upgradeVerts_(std::vector<Vertex_t>& verts) const;

    Type m_type;
};

class TextureZoneMaterial;

template <typename Vertex_t>
void
Material::upgradeVerts(std::vector<Vertex_t>& verts) const
{
    switch (m_type)
    {
        case Type::TEXTURE_ZONE:
            upgradeVerts_<Vertex_t, TextureZoneMaterial>(verts);

            break;

        default:
            break;
    }
}

} // namespace kusengine::render

#endif // MATERIAL_NOT_FULL_HPP
