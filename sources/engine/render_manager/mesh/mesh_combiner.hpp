#ifndef MESH_COMBINER_HPP
#define MESH_COMBINER_HPP

#include "engine/render_manager/buffers/gpu_buffer.hpp"
#include "engine/render_manager/buffers/index_buffer.hpp"

namespace kusengine
{
namespace render
{

struct RangeInfo
{
    uint32_t vertex_offset  = 0;
    uint32_t index_count    = 0;
    uint32_t first_index    = 0;
    uint32_t instance_count = 0;
    uint32_t first_instance = 0;
};

template <typename VertexT>
class Model;

template <typename VertexT>
class MeshCombiner
{
public:
    MeshCombiner() = default;

    void combine(
        const std::vector<std::pair<Model<VertexT>, uint32_t>>& models);

    void bindBuffers(const vk::CommandBuffer& command_buffer) const;

    void draw(const vk::CommandBuffer& command_buffer, uint32_t index) const;

private:
    std::vector<RangeInfo> m_ranges_info;

    GpuVertexBuffer m_mesh_buffer;

    IndexBuffer m_index_buffer;
};

template <typename VertexT>
void
MeshCombiner<VertexT>::combine(
    const std::vector<std::pair<Model<VertexT>, uint32_t>>& models)
{
    std::vector<typename VertexT::Attributes> all_vertices;
    std::vector<uint32_t> all_indices;

    m_ranges_info.reserve(models.size());

    RangeInfo range_info{};

    for (auto& model : models)
    {
        range_info.vertex_offset = all_vertices.size();
        range_info.first_index   = all_indices.size();
        model.first.pushMeshData(all_vertices, all_indices);

        range_info.index_count    = all_indices.size() - range_info.first_index;
        range_info.instance_count = model.second;

        m_ranges_info.emplace_back(range_info);
        range_info.first_instance += model.second;
    }

    if (all_vertices.size() == 0 || all_indices.size() == 0) return;

    m_mesh_buffer.setDataTrowStagingBuffer(
        all_vertices.data(),
        all_vertices.size() * VertexT::countFloats() * sizeof(float));

    m_index_buffer.setData(all_indices.data(),
                           all_indices.size() * sizeof(uint32_t));
}

template <typename VertexT>
void
MeshCombiner<VertexT>::bindBuffers(
    const vk::CommandBuffer& command_buffer) const
{
    m_mesh_buffer.bind(command_buffer);
    m_index_buffer.bind(command_buffer);
}

template <typename VertexT>
void
MeshCombiner<VertexT>::draw(const vk::CommandBuffer& command_buffer,
                            uint32_t index) const
{
    m_index_buffer.draw(command_buffer, m_ranges_info[index].index_count,
                        m_ranges_info[index].instance_count,
                        m_ranges_info[index].first_index,
                        m_ranges_info[index].vertex_offset,
                        m_ranges_info[index].first_instance);
}

}; // namespace render
}; // namespace kusengine

#endif // MESH_COMBINER_HPP
