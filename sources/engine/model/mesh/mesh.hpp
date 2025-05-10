#ifndef MESH_HPP
#define MESH_HPP

#include "engine/model/vertex/vertex.hpp"

namespace kusengine
{
template <typename _VertexType>
class Mesh
{
public:
    using VertexType = _VertexType;

    Mesh() = default;

    void setVertices(const std::vector<VertexType>& vertices);
    void setVertices(const std::initializer_list<VertexType>& vertices);

    void setIndices(const std::vector<uint32_t>& indices);

    const std::vector<UniversalVertexAttributes>& getVertices() const;
    const std::vector<uint32_t>& getIndices() const;

    uint32_t getVertexCount() const;

private:
    std::vector<UniversalVertexAttributes> m_vertices;

    std::vector<uint32_t> m_indices;
};

template <typename VertexType>
void
Mesh<VertexType>::setVertices(const std::vector<VertexType>& vertices)
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
template <typename VertexType>
void
Mesh<VertexType>::setVertices(const std::initializer_list<VertexType>& vertices)
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

template <typename VertexType>
void
Mesh<VertexType>::setIndices(const std::vector<uint32_t>& indices)
{
    m_indices = indices;
}
template <typename VertexType>
const std::vector<UniversalVertexAttributes>&
Mesh<VertexType>::getVertices() const
{
    return m_vertices;
}

template <typename VertexType>
const std::vector<uint32_t>&
Mesh<VertexType>::getIndices() const
{
    return m_indices;
}
template <typename VertexType>
uint32_t
Mesh<VertexType>::getVertexCount() const
{
    return m_vertices.size();
}

}; // namespace kusengine

#endif // MESH_HPP
