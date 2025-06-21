#ifndef MODEL_STORAGE_HPP
#define MODEL_STORAGE_HPP

#include <set>
#include <unordered_map>

#include "engine/render_manager/mesh/mesh_combiner.hpp"

#include "model.hpp"

namespace kusengine
{
namespace render
{
class SwapChainFrame;

template <typename VertexType>
class ModelStorage
{
public:
    ModelStorage() = default;

    uint32_t addModel(Model<VertexType>& model);

    void fillBuffers();

    void bind(const vk::CommandBuffer&) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const;

private:
    MeshCombiner<VertexType> m_mesh_combiner;

    // std::vector<uint32_t> m_order;

    std::vector<std::pair<Model<VertexType>, uint32_t>> m_models;
};

template <typename VertexType>
uint32_t
ModelStorage<VertexType>::addModel(Model<VertexType>& model)
{
    return model.pushThis(m_models);
}

template <typename VertexType>
void
ModelStorage<VertexType>::fillBuffers()
{
    m_mesh_combiner.combine(m_models);
}

template <typename VertexType>
void
ModelStorage<VertexType>::bind(const vk::CommandBuffer& command_buffer) const
{
    m_mesh_combiner.bindBuffers(command_buffer);
}

template <typename VertexType>
void
ModelStorage<VertexType>::draw(const vk::CommandBuffer& command_buffer,
                               const vk::PipelineLayout& pipelayout) const
{
    for (int model_index = 0; model_index < m_models.size(); ++model_index)
    {
        m_models[model_index].first.bindTexture(command_buffer, pipelayout);

        m_mesh_combiner.draw(command_buffer, model_index);
    }
}

}; // namespace render
}; // namespace kusengine

#endif // MODEL_STORAGE_HPP
