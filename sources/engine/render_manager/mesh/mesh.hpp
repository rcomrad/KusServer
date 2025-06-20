#ifndef MESH_HPP
#define MESH_HPP
#include "engine/render_manager/vertex/vertex.hpp"

namespace kusengine
{
namespace render
{

template <typename VertexType>
class Mesh
{
    friend bool operator==(const Mesh& left, const Mesh& right);

public:
    Mesh() = default;

    Mesh(const std::vector<uint32_t>& indices,
         const std::vector<VertexType>& vertices);

    void setVertices(const std::vector<VertexType>& vertices);
    // void setVertices(const std::initializer_list<UniversalVertex>& vertices);

    void setIndices(const std::vector<uint32_t>& indices);

    void pushData(std::vector<typename VertexType::Attributes>& vertices,
                  std::vector<uint32_t>& indices) const;

private:
    std::vector<typename VertexType::Attributes> m_vertices;

    std::vector<uint32_t> m_indices;
};

template <typename VertexType>
Mesh<VertexType>::Mesh(const std::vector<uint32_t>& indices,
                       const std::vector<VertexType>& vertices)
{
    setIndices(indices);
    setVertices(vertices);
}

template <typename VertexType>
void
Mesh<VertexType>::setVertices(const std::vector<VertexType>& vertices)
{
    size_t size = vertices.size();

    m_vertices.resize(size);

    for (size_t i = 0; i < size; ++i)
    {
        m_vertices[i] = *(vertices[i].data());
    }
}

template <typename VertexType>
void
Mesh<VertexType>::setIndices(const std::vector<uint32_t>& indices)
{
    m_indices = indices;
}
template <typename VertexType>
void
Mesh<VertexType>::pushData(
    std::vector<typename VertexType::Attributes>& vertices,
    std::vector<uint32_t>& indices) const
{
    // Vertices

    int vert_count    = m_vertices.size();
    int old_vert_size = vertices.size();

    vertices.resize(vert_count + vertices.size());

    std::copy(m_vertices.data(), m_vertices.data() + vert_count,
              vertices.data() + old_vert_size);

    // Indices

    int ind_count    = m_indices.size();
    int old_ind_size = indices.size();

    indices.resize(ind_count + indices.size());

    std::copy(m_indices.data(), m_indices.data() + ind_count,
              indices.data() + old_ind_size);
}

template <typename VertexType>
bool
operator==(const Mesh<VertexType>& left, const Mesh<VertexType>& right)
{
    return left.m_vertices == right.m_vertices &&
           left.m_indices == right.m_indices;
}
}; // namespace render
}; // namespace kusengine

#endif // MESH_HPP
