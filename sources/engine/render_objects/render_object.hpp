#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include <functional>
#include <memory>

#include "engine/render_objects/model/model_storage.hpp"
#include "engine/render_objects/objects_data/object_dynamics_data.hpp"

namespace kusengine
{
class RenderObject
{
public:
    // RenderObject() = default;

    RenderObject(std::shared_ptr<const Mesh> mesh,
                 std::shared_ptr<const Texture> texture);

    void linkDynamicsData(ObjectDynamicsData* const dd_ref);

    void setDynamicsData(const ObjectDynamicsData& dd);

    int pushModelData(std::vector<std::pair<Model, uint32_t>>& models) const;

    // bool compareModelData(const Model& other_model) const;

private:
    // std::reference_wrapper<ModelStorage> model_storage_ref;

    Model m_model;

    ObjectDynamicsData* dynamics_data_ptr;
};
}; // namespace kusengine

#endif // RENDER_OBJECT_HPP
