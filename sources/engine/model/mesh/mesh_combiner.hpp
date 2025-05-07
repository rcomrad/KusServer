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

    void combine(const std::vector<std::pair<Model, int>>& models);

    void draw(const vk::CommandBuffer& command_buffer) const;

private:
    struct RangeInfo
    {
        uint32_t vertex_offset;
        uint32_t index_count;
        uint32_t first_index;
        uint32_t instance_count;
        uint32_t first_instance;
    };

    std::vector<RangeInfo> m_ranges_info;

    void calculateCounts(const std::vector<std::pair<Model, int>>& models);

    bool has_data_flag;

    uint32_t m_index_count;

    uint32_t m_vertex_float_count;

    GpuVertexBuffer m_mesh_buffer;

    IndexBuffer m_index_buffer;
};
}; // namespace kusengine

#endif // MESH_COMBINER_HPP
