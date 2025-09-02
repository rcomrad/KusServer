#ifndef MESH_HPP
#define MESH_HPP

#include <algorithm>
#include <vector>

#include "engine/render_manager/material/material.hpp"
#include "engine/render_manager/model/bind_info.hpp"

namespace kusengine::render
{
template <typename Vertex_t>
class Mesh
{
public:
    virtual ~Mesh() = default;

    void setVerts(const std::vector<Vertex_t>& verts);

    void setInds(const std::vector<uint32_t>& inds);

    void setMaterial(const Material* const material);

    void pushDataTo(std::vector<float>& verts,
                    std::vector<uint32_t>& inds,
                    DrawInfo& draw_info,
                    BindPipelineInfo& bind_info) const;

private:
    const Material* m_material;

    std::vector<float> m_vertices;

    std::vector<uint32_t> m_indices;
};

template <typename Vertex_t>
void
Mesh<Vertex_t>::setVerts(const std::vector<Vertex_t>& verts)
{
    m_vertices.reserve(Vertex_t{}.floatCount() * verts.size());

    for (int i = 0; i < verts.size(); ++i)
    {
        verts[i].pushTo(m_vertices);
    }
}

template <typename Vertex_t>
void
Mesh<Vertex_t>::setInds(const std::vector<uint32_t>& inds)
{
    if (*(std::max_element(inds.begin(), inds.end())) >= m_vertices.size())
    {
        throw std::exception{"max index in inds for mesh is >= verts size"};
    }
    m_indices = inds;
}

template <typename Vertex_t>
void
Mesh<Vertex_t>::pushDataTo(std::vector<float>& verts,
                           std::vector<uint32_t>& inds,
                           DrawInfo& draw_info,
                           BindPipelineInfo& bind_info) const
{
    verts.reserve(verts.size() + m_vertices.size());
    inds.reserve(inds.size() + m_indices.size());

    bind_info.pipeline_key.material_type = m_material->getType();
    bind_info.pipeline_key.vertex_type   = Vertex_t{}.getType();

    draw_info.first_index   = inds.size();
    draw_info.vertex_offset = verts.size();
    draw_info.index_count   = m_indices.size();

    for (int i = 0; i < m_vertices.size(); ++i)
    {
        verts.emplace_back(m_vertices[i]);
    }
    for (int i = 0; i < m_indices.size(); ++i)
    {
        inds.emplace_back(m_indices[i]);
    }
}

template <typename Vertex_t>
void
Mesh<Vertex_t>::setMaterial(const Material* const material)
{
    m_material = material;
}

} // namespace kusengine::render

#endif // MESH_HPP
