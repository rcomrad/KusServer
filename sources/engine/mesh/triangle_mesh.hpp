#ifndef TRIANGLE_MESH
#define TRIANGLE_MESH

#include "engine/buffers/vertex_buffer.hpp"
#include "engine/device/device.hpp"

namespace kusengine
{
class TriangleMesh
{
public:
    TriangleMesh(const Device& device);

    void create(const Device& device);

private:
    VertexBuffer m_vertex_buffer;
};
}; // namespace kusengine

#endif // TRIANGLE_MESH
