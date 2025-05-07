#include "mesh_combiner.hpp"

#include "engine/model/model.hpp"

namespace kusengine
{

MeshCombiner::MeshCombiner() : m_index_count(0), has_data_flag(false)
{
}

void
MeshCombiner::calculateCounts(const std::vector<std::pair<Model, int>>& models)
{
    for (auto& model : models)
    {
        m_index_count += model.first.getMesh().getIndices().size();
        m_vertex_float_count += model.first.getMesh().getVertices().size();
    }
}

void
MeshCombiner::combine(const std::vector<std::pair<Model, int>>& models)
{
    calculateCounts(models);

    std::vector<float> all_vertices(m_vertex_float_count);
    std::vector<uint32_t> all_indices(m_index_count);

    m_ranges_info.resize(models.size());

    RangeInfo range_info;
    range_info.first_index    = 0;
    range_info.first_instance = 0;
    range_info.vertex_offset  = 0;

    int vertex_float_count = 0;

    for (auto& model : models)
    {
        auto& mesh = model.first.getMesh();

        range_info.index_count    = mesh.getIndices().size();
        range_info.instance_count = model.second;
        m_ranges_info.emplace_back(range_info);
        // copy data

        std::copy(mesh.getIndices().data(),
                  mesh.getIndices().data() + mesh.getIndices().size(),
                  all_indices.data() + range_info.first_index);

        std::copy(mesh.getVertices().data(),
                  mesh.getVertices().data() + mesh.getVertices().size(),
                  all_vertices.data() + vertex_float_count);

        vertex_float_count += mesh.getVertices().size();

        // offsets
        range_info.vertex_offset += mesh.getVertices().size();
        range_info.first_index += range_info.index_count;
        range_info.first_instance += range_info.first_instance;
    }

    if (all_vertices.size() == 0 || all_indices.size() == 0) return;

    m_mesh_buffer.setDataTrowStagingBuffer(
        all_vertices.data(), m_vertex_float_count * sizeof(float));

    m_index_buffer.setData(all_indices.data(),
                           m_index_count * sizeof(uint32_t));

    has_data_flag = true;
}

void
MeshCombiner::draw(const vk::CommandBuffer& command_buffer) const
{
    if (!has_data_flag) return;
    m_mesh_buffer.bind(command_buffer);
    m_index_buffer.bind(command_buffer);

    for (int i = 0; i < m_ranges_info.size(); ++i)
    {
        m_index_buffer.draw(
            command_buffer, m_ranges_info[i].index_count,
            m_ranges_info[i].instance_count, m_ranges_info[i].first_index,
            m_ranges_info[i].vertex_offset, m_ranges_info[i].first_instance);
    }
}
}; // namespace kusengine
