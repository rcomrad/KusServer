#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "engine/model/mesh/mesh_factory.hpp"

namespace kusengine
{

void
Scene::create(float width, float height)
{
    // Models
    m_models.resize(3);

    Mesh<UniversalVertex> mesh;

    // First Model
    mesh = MESH_FACTORY.createUniversalRectangleMesh({-1, -1}, {0.5, 0.5},
                                                     {0, 0, 0});
    m_models[0].setMesh(mesh);

    // Second Model
    mesh = MESH_FACTORY.createUniversalRectangleMesh({0, -0.1}, {0.5, 0.5},
                                                     {0, 0, 1});
    m_models[1].setMesh(mesh);

    // Third Model
    mesh = MESH_FACTORY.createUniversalRectangleMesh({0.4, 0.6}, {0.5, 0.5},
                                                     {1, 0, 1});
    m_models[2].setMesh(mesh);

    // Camera
    m_camera.setAspectRatio(width / height);

    m_mesh_combiner.combine(m_models);
    // m_dynamic_objects_data.m_dynamic_objects_data.resize(m_models.size(),
    //                                                      {
    //                                                          {0, 0}
    // });
}

const UBO&
Scene::ubo() const
{
    return {m_camera.getViewProjection()};
}

const DynamicObjectsData&
Scene::dynamicObjectsData() const
{
    return m_dynamic_objects_data;
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
