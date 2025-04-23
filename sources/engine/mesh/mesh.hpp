#ifndef MESH_HPP
#define MESH_HPP

#include "engine/buffers/vertex_buffer.hpp"

#include "vertex.hpp"

namespace kusengine
{
template <typename Vt>
class Mesh
{
public:
    using VertexType = Vt;

    Mesh() = default;

    void setVertices(const std::vector<VertexType>& vertices);
    void setVertices(const std::initializer_list<VertexType>& vertices);

    void setIndices(const std::vector<uint32_t>& indices);

    size_t vertexCount() const noexcept;
    size_t indexCount() const noexcept;

    const float* const verticesData() const noexcept;
    const uint32_t* const indicesData() const noexcept;

private:
    std::vector<float> m_vertices_data;

    std::vector<uint32_t> m_indices_data;

    size_t m_vertex_count;
};

template <typename Vt>
void
Mesh<Vt>::setVertices(const std::vector<VertexType>& vertices)
{
    size_t size = vertices.size();
    if (size == 0) return;

    m_vertex_count   = size;
    int count_floats = VertexType::countFloats();
    m_vertices_data.resize(size * count_floats);

    for (size_t i = 0; i < size; ++i)
    {
        std::copy(vertices[i].data(), vertices[i].data() + count_floats,
                  m_vertices_data.data() + i * count_floats);
    }
}
template <typename Vt>
void
Mesh<Vt>::setVertices(const std::initializer_list<VertexType>& vertices)
{
    size_t size = vertices.size();
    if (size == 0) return;

    m_vertex_count   = size;
    int count_floats = VertexType::countFloats();
    m_vertices_data.resize(size * count_floats);

    for (size_t i = 0; i < size; ++i)
    {
        std::copy((vertices.begin() + i)->data(),
                  (vertices.begin() + i)->data() + count_floats,
                  m_vertices_data.data() + i * count_floats);
    }
}

template <typename Vt>
void
Mesh<Vt>::setIndices(const std::vector<uint32_t>& indices)
{
    m_indices_data = indices;
}

template <typename Vt>
size_t
Mesh<Vt>::vertexCount() const noexcept
{
    return m_vertex_count;
}

template <typename Vt>
size_t
Mesh<Vt>::indexCount() const noexcept
{
    return m_indices_data.size();
}

template <typename Vt>
const float* const
Mesh<Vt>::verticesData() const noexcept
{
    return m_vertices_data.data();
}

template <typename Vt>
const uint32_t* const
Mesh<Vt>::indicesData() const noexcept
{
    return m_indices_data.data();
}

}; // namespace kusengine

#endif // MESH_HPP
