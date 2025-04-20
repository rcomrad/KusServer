#ifndef TRIANGLE_MESH
#define TRIANGLE_MESH

#include "engine/buffers/vertex_buffer.hpp"
#include "engine/commands/command_buffer.hpp"
#include "engine/device/device.hpp"

namespace kusengine
{

class TriangleMesh
{
public:
    TriangleMesh(const Device& device);

    void create();

    void draw(const vk::CommandBuffer& command_buffer) const;

    template <typename Iter>
    void setVertices(Iter begin, Iter end);

private:
    uint32_t m_vertices_count;

    VertexBuffer m_vertex_buffer;
};

template <typename Iter>
void
TriangleMesh::setVertices(Iter begin, Iter end)
{
    if (begin == end) return;
    m_vertices_count = (end - begin) / 5;
    m_vertex_buffer.setVertices({begin, end});
}
}; // namespace kusengine

#endif // TRIANGLE_MESH
