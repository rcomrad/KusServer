#include "mesh.hpp"

namespace kusengine
{

// void
// Mesh::setVertices(const std::vector<UniversalVertex>& vertices)
// {
//     size_t size = vertices.size();
//     if (size == 0) return;

//     m_count_vertex   = size;
//     int count_floats = UniversalVertex::countFloats();
//     m_vertices_data.resize(size * count_floats);

//     for (size_t i = 0; i < size; ++i)
//     {
//         std::copy(vertices[i].data(), vertices[i].data() + count_floats,
//                   m_vertices_data.data() + i * count_floats);
//     }
// }

// void
// Mesh::setVertices(const std::initializer_list<UniversalVertex>& vertices)
// {
//     size_t size = vertices.size();
//     if (size == 0) return;

//     m_count_vertex   = size;
//     int count_floats = UniversalVertex::countFloats();
//     m_vertices_data.resize(size * count_floats);

//     for (size_t i = 0; i < size; ++i)
//     {
//         std::copy((vertices.begin() + i)->data(),
//                   (vertices.begin() + i)->data() + count_floats,
//                   m_vertices_data.data() + i * count_floats);
//     }
// }

// size_t
// Mesh::countVertex() const noexcept
// {
//     return m_count_vertex;
// }

// const float* const
// Mesh::data() const noexcept
// {
//     return m_vertices_data.data();
// }

}; // namespace kusengine
