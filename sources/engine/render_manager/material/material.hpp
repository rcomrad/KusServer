#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "material_not_full.hpp"
#include "texture_zone_material.hpp"

namespace kusengine::render
{
template <typename Vertex_t, typename Material_t>
void
Material::upgradeVerts_(std::vector<Vertex_t>& verts) const
{
    static_cast<const Material_t*>(this)->upgradeVertsConcreateImpl(verts);
}
}; // namespace kusengine::render

#endif // MATERIAL_HPP
