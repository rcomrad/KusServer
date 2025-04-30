#include "mesh_combiner.hpp"

#include "model.hpp"
namespace kusengine
{

MeshCombiner::MeshCombiner() : m_index_count(0)
{
}

void
MeshCombiner::calculateCounts(const std::vector<Model>& models)
{
    for (auto& model : models)
    {
        m_index_count += model.getMesh().getIndices().size();
        m_vertex_count += model.getMesh().getVertices().size();
    }
}

void
MeshCombiner::combine(const std::vector<Model>& models)
{
    calculateCounts(models);

    std::vector<float> all_vertices(m_vertex_count);
    std::vector<uint32_t> all_indices(m_index_count);

    int index_count  = 0;
    int vertex_count = 0;

    for (auto& model : models)
    {
        auto& mesh = model.getMesh();

        auto&& vertices = mesh.getVertices();
        auto&& indices  = mesh.getIndices();

        std::copy(vertices.data(), vertices.data() + vertices.size(),
                  all_vertices.data() + vertex_count);

        std::copy(indices.data(), indices.data() + indices.size(),
                  all_indices.data() + index_count);

        index_count += indices.size();
        vertex_count += vertices.size();
    }

    m_mesh_buffer.setDataTrowStagingBuffer(all_vertices.data(), m_vertex_count * sizeof(float));
    m_index_buffer.setData(all_indices.data(),
                           m_index_count * sizeof(uint32_t));
}

void
MeshCombiner::draw(const vk::CommandBuffer& command_buffer) const
{
    m_mesh_buffer.bind(command_buffer);
    m_index_buffer.bind(command_buffer);
    m_index_buffer.draw(command_buffer, m_index_count);
}
}; // namespace kusengine
