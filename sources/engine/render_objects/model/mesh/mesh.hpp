#ifndef MESH_HPP
#define MESH_HPP
#include "engine/render_objects/model/vertex/vertex.hpp"

namespace kusengine
{
class Mesh
{
    friend bool operator==(const Mesh& left, const Mesh& right);

public:
    Mesh() = default;

    void setVertices(const std::vector<UniversalVertex>& vertices);
    void setVertices(const std::initializer_list<UniversalVertex>& vertices);

    void setIndices(const std::vector<uint32_t>& indices);

    void pushData(std::vector<UniversalVertexAttributes>& vertices,
                  std::vector<uint32_t>& indices) const;

private:
    std::vector<UniversalVertexAttributes> m_vertices;

    std::vector<uint32_t> m_indices;
};

bool
operator==(const Mesh& left, const Mesh& right);

}; // namespace kusengine

#endif // MESH_HPP
