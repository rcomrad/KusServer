#include "model.hpp"

namespace kusengine
{
// void
// Model::create()
// {
//     std::vector<UniversalVertex> rectangle = {
//         {-1, -1, 0.3, 1,   0.5},
//         {1,  -1, 0.1, 1,   0.8},
//         {1,  1,  0.6, 0.2, 0.5},
//         {-1, 1,  0.3, 0,   1  }
//     };
//     m_mesh.setVertices(rectangle);

//     std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};
//     m_mesh.setIndices(indices);
// }

void
Model::setMesh(const Mesh<UniversalVertex>& mesh)
{
    m_mesh = mesh;
}
void
Model::setMesh(Mesh<UniversalVertex>&& mesh)
{
    m_mesh = mesh;
}

const Mesh<UniversalVertex>&
Model::getMesh() const
{
    return m_mesh;
}
}; // namespace kusengine
