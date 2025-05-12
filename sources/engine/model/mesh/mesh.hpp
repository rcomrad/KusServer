#ifndef MESH_HPP
#define MESH_HPP

#include "engine/model/vertex/vertex.hpp"

namespace kusengine
{
class Mesh
{
public:
    Mesh() = default;

    void setVertices(const std::vector<UniversalVertex>& vertices);
    void setVertices(const std::initializer_list<UniversalVertex>& vertices);

    void setIndices(const std::vector<uint32_t>& indices);

    const std::vector<UniversalVertexAttributes>& getVertices() const;
    const std::vector<uint32_t>& getIndices() const;

    uint32_t getVertexCount() const;

private:
    std::vector<UniversalVertexAttributes> m_vertices;

    std::vector<uint32_t> m_indices;
};

}; // namespace kusengine

#endif // MESH_HPP
