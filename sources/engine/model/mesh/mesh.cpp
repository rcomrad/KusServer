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
void
Mesh::setVertices(const std::initializer_list<UniversalVertex>& vertices)
{
    size_t size = vertices.size();

    m_vertices.resize(size);

    for (size_t i = 0; i < size; ++i)
    {
        m_vertices[i] = *((vertices.begin() + i)->data());
    }
}

void
Mesh::setIndices(const std::vector<uint32_t>& indices)
{
    m_indices = indices;
}
const std::vector<UniversalVertexAttributes>&
Mesh::getVertices() const
{
    return m_vertices;
}

const std::vector<uint32_t>&
Mesh::getIndices() const
{
    return m_indices;
}

uint32_t
Mesh::getVertexCount() const
{
    return m_vertices.size();
}
}; // namespace kusengine
