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
    RangeInfo();

    uint32_t vertex_offset;
    uint32_t index_count;
    uint32_t first_index;
    uint32_t instance_count;
    uint32_t first_instance;
};

template <typename VertexType>
class Model;

template <typename VertexType>
class MeshCombiner
{
public:
    MeshCombiner() = default;

    void combine(
        const std::vector<std::pair<Model<VertexType>, uint32_t>>& models);

    void bindBuffers(const vk::CommandBuffer& command_buffer) const;

    void draw(const vk::CommandBuffer& command_buffer, uint32_t index) const;

private:
    std::vector<RangeInfo> m_ranges_info;

    GpuVertexBuffer m_mesh_buffer;

    IndexBuffer m_index_buffer;
};

template <typename VertexType>
void
MeshCombiner<VertexType>::combine(
    const std::vector<std::pair<Model<VertexType>, uint32_t>>& models)
{
    std::vector<VertexType> all_vertices;
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

    m_mesh_buffer.setDataTrowStagingBuffer(
        all_vertices.data(), all_vertices.size() *
                                 VertexType::Attributes::count_floats *
                                 sizeof(float));

    m_index_buffer.setData(all_indices.data(),
                           all_indices.size() * sizeof(uint32_t));
}

template <typename VertexType>
void
MeshCombiner<VertexType>::bindBuffers(
    const vk::CommandBuffer& command_buffer) const
{
    m_mesh_buffer.bind(command_buffer);
    m_index_buffer.bind(command_buffer);
}

template <typename VertexType>
void
MeshCombiner<VertexType>::draw(const vk::CommandBuffer& command_buffer,
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
