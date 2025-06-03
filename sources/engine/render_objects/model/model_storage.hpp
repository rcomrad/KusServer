#ifndef MODEL_STORAGE_HPP
#define MODEL_STORAGE_HPP

#include <set>
#include <unordered_map>

#include "engine/render_objects/model/mesh/mesh_combiner.hpp"
#include "engine/render_objects/objects_data/model_basic_dynamics_data.hpp"

#include "model.hpp"

namespace kusengine
{

class RenderObject;
class SwapChainFrame;

class ModelStorage
{
public:
    ModelStorage();

    void addRenderObject(RenderObject& render_object);

    void fillBuffers();

    void bind(const vk::CommandBuffer&) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const;

    const std::vector<MBDD>& getMBDD() const;

private:
    MeshCombiner m_mesh_combiner;

    std::vector<std::pair<Model, uint32_t>> m_models; // TODO: combine!

    // TODO: unite
    std::vector<MBDD> mbdd_data_vector;
};
}; // namespace kusengine

#endif // MODEL_STORAGE_HPP
