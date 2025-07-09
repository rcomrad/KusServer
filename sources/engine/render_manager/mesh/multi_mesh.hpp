#ifndef MULTI_MESH_HPP
#define MULTI_MESH_HPP

#include <vector>

#include "mesh.hpp"

namespace kusengine::render
{

class MultiMesh final
{
public:
    size_t size() const noexcept;

    const Mesh* const get() const noexcept;

private:
    std::vector<const Mesh*> m_meshes;
};

// template <typename VertexT>
// Mesh<VertexT>::Mesh(const std::vector<uint32_t>& indices,
//                     const std::vector<VertexT>& vertices)
// {
//     setIndices(indices);
//     setVertices(vertices);
// }

// template <typename VertexT>
// void
// Mesh<VertexT>::setVertices(const std::vector<VertexT>& vertices)
// {
//     size_t size = vertices.size();

//     m_vertices.resize(size);

//     for (size_t i = 0; i < size; ++i)
//     {
//         m_vertices[i] = *(vertices[i].data());
//     }
// }

// template <typename VertexT>
// void
// Mesh<VertexT>::setIndices(const std::vector<uint32_t>& indices)
// {
//     m_indices = indices;
// }
// template <typename VertexT>
// void
// Mesh<VertexT>::pushData(std::vector<typename VertexT::Attributes>& vertices,
//                         std::vector<uint32_t>& indices) const
// {
//     // Vertices

//     int vert_count    = m_vertices.size();
//     int old_vert_size = vertices.size();

//     vertices.resize(vert_count + vertices.size());

//     std::copy(m_vertices.data(), m_vertices.data() + vert_count,
//               vertices.data() + old_vert_size);

//     // Indices

//     int ind_count    = m_indices.size();
//     int old_ind_size = indices.size();

//     indices.resize(ind_count + indices.size());

//     std::copy(m_indices.data(), m_indices.data() + ind_count,
//               indices.data() + old_ind_size);
// }

}; // namespace render
}
; // namespace kusengine

#endif // MULTI_MESH_HPP
