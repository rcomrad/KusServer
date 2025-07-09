#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "engine/render_manager/material/material.hpp"

namespace kusengine::render
{
class Mesh
{
public:
    virtual ~Mesh();

    template <typename Vert_t>
    void setVerts(const std::vector<Vert_t>& verts);

    void setInds(const std::vector<float>& inds);

private:
    const Material* const m_material;

    std::vector<float> m_vertices;

    std::vector<float> m_indices;
};

template <typename Vert_t>
void
Mesh::setVerts(const std::vector<Vert_t>& verts)
{
    m_vertices.reserve(Vert_t::floatCount() * verts.size());

    for (int i = 0; i < verts.size(); ++i)
    {
        verts[i].pushTo(m_vertices);
    }
}

} // namespace kusengine::render

#endif // MESH_HPP
