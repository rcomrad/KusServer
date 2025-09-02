#ifndef MESH_HPP
#define MESH_HPP

#include <algorithm>
#include <vector>

#include "engine/render_manager/material/material.hpp"
#include "engine/render_manager/vertex/vertex.hpp"

namespace kusengine::render
{
struct IMesh
{
    virtual ~IMesh() = default;

    IMesh(VertexType vt, int vert_byte_size);

    void setInds(const std::vector<uint32_t>& inds);

    const Material* getMaterial() const noexcept;

    virtual void setVertices(const std::vector<char>& verts_char) = 0;

    virtual void setMaterial(const Material* const material) = 0;

    virtual std::pair<size_t, size_t> pushDataTo(
        std::vector<char>& verts,
        std::vector<uint32_t>& inds) const = 0;

    virtual VertexType getVertType() const noexcept = 0;

protected:
    VertexType m_vertex_type;

    int m_vertex_byte_size;

    std::vector<uint32_t> m_indices;

    const Material* m_material;
};

template <typename Vertex_t>
class Mesh final : public IMesh
{
public:
    virtual ~Mesh() = default;

    Mesh();

    void setVertices(const std::vector<char>& verts_char) override;

    void setMaterial(const Material* const material) override;

    std::pair<size_t, size_t> pushDataTo(
        std::vector<char>& verts,
        std::vector<uint32_t>& inds) const override;

    VertexType getVertType() const noexcept override;

private:
    std::vector<Vertex_t> m_vertices;
};

template <typename Vertex_t>
Mesh<Vertex_t>::Mesh() : IMesh(Vertex_t{}.getType(), Vertex_t{}.byteSize())
{
}

template <typename Vertex_t>
void
Mesh<Vertex_t>::setVertices(const std::vector<char>& verts_char)
{
    if (verts_char.size() % m_vertex_byte_size != 0)
    {
        throw std::exception("error in set verts error in mesh");
    }
    m_vertices.resize(verts_char.size() / m_vertex_byte_size);

    for (int i = 0; i < m_vertices.size(); ++i)
    {
        m_vertices[i].getDataFrom(verts_char, i * m_vertex_byte_size);
    }
}

template <typename Vertex_t>
std::pair<size_t, size_t>
Mesh<Vertex_t>::pushDataTo(std::vector<char>& verts,
                           std::vector<uint32_t>& inds) const
{
    verts.reserve(verts.size() + m_vertices.size() * m_vertex_byte_size);
    inds.reserve(inds.size() + m_indices.size());

    for (int i = 0; i < m_vertices.size(); ++i)
    {
        m_vertices[i].pushTo(verts);
    }
    for (int i = 0; i < m_indices.size(); ++i)
    {
        inds.emplace_back(m_indices[i]);
    }
    return {m_vertices.size(), m_indices.size()};
}
template <typename Vertex_t>
void
Mesh<Vertex_t>::setMaterial(const Material* const material)
{
    material->upgradeVerts(m_vertices);

    m_material = material;
}

template <typename Vertex_t>
VertexType
Mesh<Vertex_t>::getVertType() const noexcept
{
    return m_vertex_type;
}

} // namespace kusengine::render

#endif // MESH_HPP
