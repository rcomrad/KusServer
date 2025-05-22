#include "model_storage.hpp"

#include "engine/render_objects/render_object.hpp"

namespace kusengine
{

uint32_t ModelStorage::m_storage_count  = 0;
uint32_t ModelStorage::m_last_binded_id = -1;

ModelStorage::ModelStorage()
{
    m_id = m_storage_count++;
}

const std::vector<ObjectDynamicsData>&
ModelStorage::objDynData() const
{
    return object_dynamics_data_vector;
}

void
ModelStorage::addRenderObject(RenderObject& render_object,
                              const ObjectDynamicsData& dd)
{
    render_object.pushModelData(m_models);

    object_dynamics_data_vector.emplace_back(dd);
    render_object.linkDynamicsData(
        &(object_dynamics_data_vector[object_dynamics_data_vector.size() - 1]));
}

void
ModelStorage::fillBuffers()
{
    m_mesh_combiner.combine(m_models);
}

bool
ModelStorage::wasLastBinded() const
{
    return m_last_binded_id == m_id;
}

void
ModelStorage::bind(const vk::CommandBuffer& command_buffer) const
{
    m_last_binded_id = m_id;

    m_mesh_combiner.bindBuffers(command_buffer);
}

void
ModelStorage::draw(const vk::CommandBuffer& command_buffer,
                   const vk::PipelineLayout& pipelayout) const
{

    for (int obj_index = 0; obj_index < m_models.size(); ++obj_index)
    {
        m_models[obj_index].first.bind(command_buffer, pipelayout);

        m_mesh_combiner.draw(command_buffer, obj_index);
    }
}

}; // namespace kusengine
