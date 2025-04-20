#include "triangle_mesh.hpp"

namespace kusengine
{
TriangleMesh::TriangleMesh(const Device& device) : m_vertex_buffer(device)
{
}

// void
// TriangleMesh::setVerteces(
//     const std::vector<std::initializer_list<float>>& verteces_data)
// {
// }

void
TriangleMesh::create()
{
    std::vector<float> vertices = {0.0f,  -0.8f, 0.0f, 1.0f, 0.0f,
                                   0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
                                   -0.5f, 0.5f,  0.0f, 1.0f, 0.0f};

    setVertices(vertices.begin(), vertices.end());
}

void
TriangleMesh::draw(const vk::CommandBuffer& command_buffer) const
{
    m_vertex_buffer.bind(command_buffer);

    command_buffer.draw(m_vertices_count, 1, 0, 0);
}
}; // namespace kusengine
