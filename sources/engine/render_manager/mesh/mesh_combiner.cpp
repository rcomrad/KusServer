#include "mesh_combiner.hpp"

#include <iostream>

#include "engine/render_manager/model/model.hpp"

namespace kusengine
{
namespace render
{
MeshCombiner::RangeInfo::RangeInfo()
    : vertex_offset(0),
      index_count(0),
      first_index(0),
      instance_count(0),
      first_instance(0)
{
}

void
MeshCombiner::combine(const std::vector<std::pair<Model, uint32_t>>& models)
{
    std::vector<UniversalVertexAttributes> all_vertices;
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
                                 UniversalVertexAttributes::count_floats *
                                 sizeof(float));

    m_index_buffer.setData(all_indices.data(),
                           all_indices.size() * sizeof(uint32_t));
}

void
MeshCombiner::bindBuffers(const vk::CommandBuffer& command_buffer) const
{
    m_mesh_buffer.bind(command_buffer);
    m_index_buffer.bind(command_buffer);
}

void
MeshCombiner::draw(const vk::CommandBuffer& command_buffer,
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
