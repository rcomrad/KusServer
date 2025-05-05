#ifndef MESH_HPP
#define MESH_HPP

#include "engine/model/vertex/vertex.hpp"

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

    const std::vector<float>& getVertices() const;
    const std::vector<uint32_t>& getIndices() const;

    uint32_t getVertexCount() const;

private:
    std::vector<float> m_vertices;

    std::vector<uint32_t> m_indices;
};

template <typename Vt>
void
Mesh<Vt>::setVertices(const std::vector<VertexType>& vertices)
{
    size_t size = vertices.size();

    int count_floats = VertexType::countFloats();
    m_vertices.resize(size * count_floats);

    for (size_t i = 0; i < size; ++i)
    {
        std::copy(vertices[i].data(), vertices[i].data() + count_floats,
                  m_vertices.data() + i * count_floats);
    }
}
template <typename Vt>
void
Mesh<Vt>::setVertices(const std::initializer_list<VertexType>& vertices)
{
    size_t size = vertices.size();

    int count_floats = VertexType::countFloats();
    m_vertices.resize(size * count_floats);

    for (size_t i = 0; i < size; ++i)
    {
        std::copy((vertices.begin() + i)->data(),
                  (vertices.begin() + i)->data() + count_floats,
                  m_vertices.data() + i * count_floats);
    }
}

template <typename Vt>
void
Mesh<Vt>::setIndices(const std::vector<uint32_t>& indices)
{
    m_indices = indices;
}
template <typename Vt>
const std::vector<float>&
Mesh<Vt>::getVertices() const
{
    return m_vertices;
}

template <typename Vt>
const std::vector<uint32_t>&
Mesh<Vt>::getIndices() const
{
    return m_indices;
}
template <typename Vt>
uint32_t
Mesh<Vt>::getVertexCount() const
{
    return m_vertices.size() / Vt::countFloats();
}

}; // namespace kusengine

#endif // MESH_HPP
