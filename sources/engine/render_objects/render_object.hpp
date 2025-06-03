#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include <memory>

#include "engine/render_objects/model/model_storage.hpp"
#include "engine/render_objects/objects_data/model_basic_dynamics_data.hpp"

namespace kusengine
{
class RenderObject : public ModelBasicDynamicsDataInterface
{
public:
    RenderObject() = default;

    RenderObject(std::shared_ptr<const Mesh> mesh,
                 std::shared_ptr<const Texture> texture);

    void create(std::shared_ptr<const Mesh> mesh,
                std::shared_ptr<const Texture> texture);

    int pushModelData(std::vector<std::pair<Model, uint32_t>>& models) const;

private:
    Model m_model;
};
}; // namespace kusengine

#endif // RENDER_OBJECT_HPP
