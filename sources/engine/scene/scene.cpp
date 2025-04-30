#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace kusengine
{

void
Scene::create(float width, float height)
{
    // Models
    m_models.resize(3);

    for (auto& model : m_models)
    {
        model.create();
    }

    // Camera
    m_camera.setAspectRatio(width / height);

    m_mesh_combiner.combine(m_models);
}

UBO
Scene::ubo() const
{
    return {m_camera.getViewProjection()};
}

void
Scene::draw(const vk::CommandBuffer& command_buffer) const
{
    m_mesh_combiner.draw(command_buffer);
}

const Camera2D&
Scene::camera() const
{
    return m_camera;
}

Camera2D&
Scene::camera()
{
    return m_camera;
}
}; // namespace kusengine
