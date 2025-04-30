#ifndef MESH_COMBINER_HPP
#define MESH_COMBINER_HPP

#include "engine/buffers/gpu_buffer.hpp"
#include "engine/buffers/index_buffer.hpp"

namespace kusengine
{

class Model;

class MeshCombiner
{
public:
    MeshCombiner();

    void combine(const std::vector<Model>& models);

    void draw(const vk::CommandBuffer& command_buffer) const;

private:

    void calculateCounts(const std::vector<Model>& models);

    uint32_t m_index_count;

    uint32_t m_vertex_count;

    GpuVertexBuffer m_mesh_buffer;

    IndexBuffer m_index_buffer;
};
}; // namespace kusengine

#endif // MESH_COMBINER_HPP
