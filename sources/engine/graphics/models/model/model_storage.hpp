#ifndef MODEL_STORAGE_HPP
#define MODEL_STORAGE_HPP

#include <set>
#include <unordered_map>

#include "engine/graphics/models/dynamic_data/model_basic_dynamics_data.hpp"
#include "engine/graphics/models/model/mesh/mesh_combiner.hpp"

#include "model.hpp"

namespace kusengine
{
class SwapChainFrame;

class ModelStorage
{
public:
    ModelStorage();

    uint32_t addModel(Model& model);

    void fillBuffers();

    void bind(const vk::CommandBuffer&) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const;

private:
    MeshCombiner m_mesh_combiner;

    // std::vector<uint32_t> m_order;

    std::vector<std::pair<Model, uint32_t>> m_models; // TODO: combine!
};
}; // namespace kusengine

#endif // MODEL_STORAGE_HPP
