#ifndef MODEL_STORAGE_HPP
#define MODEL_STORAGE_HPP

#include <set>

#include "engine/render_objects/model/mesh/mesh_combiner.hpp"
#include "engine/render_objects/objects_data/object_dynamics_data.hpp"

// #include "id_mgr.hpp"
#include "model.hpp"

namespace kusengine
{

class RenderObject;

class ModelStorage
{
public:
    ModelStorage();

    void addRenderObject(RenderObject& render_object,
                         const ObjectDynamicsData& dd = {});

    void fillBuffers();

    bool wasLastBinded() const;

    void bind(const vk::CommandBuffer&) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const;

    const std::vector<ObjectDynamicsData>& objDynData() const;

private:
    static uint32_t m_storage_count;
    static uint32_t m_last_binded_id;
    uint32_t m_id;

    MeshCombiner m_mesh_combiner;

    std::vector<std::pair<Model, uint32_t>> m_models;

    std::vector<ObjectDynamicsData> object_dynamics_data_vector;
};
}; // namespace kusengine

#endif // MODEL_STORAGE_HPP
