#include "triangle_mesh.hpp"

namespace kusengine
{
TriangleMesh::TriangleMesh(const Device& device) : m_vertex_buffer(device)
{
}

void
TriangleMesh::create(const Device& device)
{
    size_t size = 15 * sizeof(float);
    m_vertex_buffer.create(size);

    std::vector<float> vertices = {0.0f,   -0.05f, 0.0f, 1.0f, 0.0f,
                                   0.05f,  0.05f,  0.0f, 1.0f, 0.0f,
                                   -0.05f, 0.05f,  0.0f, 1.0f, 0.0f};
    m_vertex_buffer.setVerteces(vertices);
}
}; // namespace kusengine
