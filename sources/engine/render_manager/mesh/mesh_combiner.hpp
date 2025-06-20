#ifndef MESH_COMBINER_HPP
#define MESH_COMBINER_HPP

#include "engine/render_manager/buffers/gpu_buffer.hpp"
#include "engine/render_manager/buffers/index_buffer.hpp"

namespace kusengine
{
namespace render
{
class Model;

class MeshCombiner
{
public:
    MeshCombiner() = default;

    void combine(const std::vector<std::pair<Model, uint32_t>>& models);

    void bindBuffers(const vk::CommandBuffer& command_buffer) const;

    void draw(const vk::CommandBuffer& command_buffer, uint32_t index) const;

private:
    struct RangeInfo
    {
        RangeInfo();

        uint32_t vertex_offset;
        uint32_t index_count;
        uint32_t first_index;
        uint32_t instance_count;
        uint32_t first_instance;
    };

    std::vector<RangeInfo> m_ranges_info;

    GpuVertexBuffer m_mesh_buffer;

    IndexBuffer m_index_buffer;
};
}; // namespace render
}; // namespace kusengine

#endif // MESH_COMBINER_HPP
