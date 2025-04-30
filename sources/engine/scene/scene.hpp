#ifndef SCENE_HPP
#define SCENE_HPP

#include <glm/glm.hpp>

#include "engine/model/mesh_combiner.hpp"
#include "engine/model/model.hpp"
#include "engine/uniform_buffer_objects/uniform_buffer_object.hpp"

#include "camera.hpp"

namespace kusengine
{

class Scene
{
public:
    Scene() = default;

    void create(float width, float height);

    void draw(const vk::CommandBuffer& command_buffer) const;

    UBO ubo() const;

    const Camera2D& camera() const;

    Camera2D& camera();

private:
    // Models

    MeshCombiner m_mesh_combiner;

    std::vector<Model> m_models;

    /////////////////////
    UBO m_ubo;

    Camera2D m_camera;
};

}; // namespace kusengine

#endif // SCENE_HPP
