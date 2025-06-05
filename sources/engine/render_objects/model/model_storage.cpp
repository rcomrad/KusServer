#include "model_storage.hpp"

#include "engine/render_objects/render_object.hpp"
#include "engine/renderer/swap_chain_frame.hpp"
namespace kusengine
{

ModelStorage::ModelStorage()
{
}

void
ModelStorage::addModel(Model& model)
{
    model.pushThis(m_models);
}

void
ModelStorage::fillBuffers()
{
    m_mesh_combiner.combine(m_models);
}

void
ModelStorage::bind(const vk::CommandBuffer& command_buffer) const
{
    m_mesh_combiner.bindBuffers(command_buffer);
}

void
ModelStorage::draw(const vk::CommandBuffer& command_buffer,
                   const vk::PipelineLayout& pipelayout) const
{
    for (int model_index = 0; model_index < m_models.size(); ++model_index)
    {
        m_models[model_index].first.bind(command_buffer, pipelayout);

        m_mesh_combiner.draw(command_buffer, model_index);
    }
}

}; // namespace kusengine
