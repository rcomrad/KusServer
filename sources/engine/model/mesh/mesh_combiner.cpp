#include "mesh_combiner.hpp"

#include "engine/model/model.hpp"

namespace kusengine
{

MeshCombiner::MeshCombiner() : m_index_count(0), has_data_flag(false)
{
}

void
MeshCombiner::calculateCounts(const std::vector<Model>& models)
{
    for (auto& model : models)
    {
        m_index_count += model.getMesh().getIndices().size();
        m_vertex_float_count += model.getMesh().getVertices().size();
    }
}

void
MeshCombiner::combine(const std::vector<Model>& models)
{
    calculateCounts(models);

    std::vector<float> all_vertices(m_vertex_float_count);
    std::vector<uint32_t> all_indices(m_index_count);

    int index_count        = 0;
    int vertex_float_count = 0;

    uint32_t vertex_count = 0;

    m_index_offsets.reserve(models.size());
    m_vertex_offsets.reserve(models.size());
    m_index_counts.reserve(models.size());

    for (auto& model : models)
    {
        auto& mesh = model.getMesh();

        // Vertex
        auto&& vertices = mesh.getVertices();
        std::copy(vertices.data(), vertices.data() + vertices.size(),
                  all_vertices.data() + vertex_float_count);

        // Index
        auto indices = mesh.getIndices();

        std::copy(indices.data(), indices.data() + indices.size(),
                  all_indices.data() + index_count);

        m_index_offsets.emplace_back(index_count);

        m_vertex_offsets.emplace_back(vertex_count);
        m_index_counts.emplace_back(static_cast<uint32_t>(indices.size()));

        vertex_count += mesh.getVertexCount();
        index_count += indices.size();
        vertex_float_count += vertices.size();
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

    for (int i = 0; i < m_index_offsets.size(); ++i)
    {
        m_index_buffer.draw(command_buffer, m_index_counts[i],
                            m_index_offsets[i], m_vertex_offsets[i]);
    }
}
}; // namespace kusengine
