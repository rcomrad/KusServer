#include "mesh.hpp"

namespace kusengine
{

void
Mesh::setVertices(const std::vector<UniversalVertex>& vertices)
{
    size_t size = vertices.size();

    m_vertices.resize(size);

    for (size_t i = 0; i < size; ++i)
    {
        m_vertices[i] = *(vertices[i].data());
    }
}
// void
// Mesh::setVertices(const std::initializer_list<UniversalVertex>& vertices)
// {
//     size_t size = vertices.size();

//     m_vertices.resize(size);

//     for (size_t i = 0; i < size; ++i)
//     {
//         m_vertices[i] = *((vertices.begin() + i)->data());
//     }
// }

void
Mesh::setIndices(const std::vector<uint32_t>& indices)
{
    m_indices = indices;
}
// const std::vector<UniversalVertexAttributes>&
// Mesh::getVertices() const
// {
//     return m_vertices;
// }
// const std::vector<uint32_t>&
// Mesh::getIndices() const
// {
//     return m_indices;
// }
// uint32_t
// Mesh::getVertexCount() const
// {
//     return m_vertices.size();
// }

void
Mesh::pushData(std::vector<UniversalVertexAttributes>& vertices,
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

bool
operator==(const Mesh& left, const Mesh& right)
{
    return left.m_vertices == right.m_vertices &&
           left.m_indices == right.m_indices;
}
}; // namespace kusengine
