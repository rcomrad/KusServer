#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <math.h>

#include "engine/model/mesh/mesh_factory.hpp"

namespace kusengine
{

void
Scene::update(float time)
{
    for (int i = 0; i < m_dynamic_objects_data.m_dynamic_objects_data.size();
         ++i)
    {
        circlec_moving_info[i][0] += circlec_moving_info[i][1] * time;

        m_dynamic_objects_data.m_dynamic_objects_data[i].position.x =
            std::cos(circlec_moving_info[i][0] / 180 * 3.14) *
            circlec_moving_info[i][2];

        m_dynamic_objects_data.m_dynamic_objects_data[i].position.y =
            std::sin(circlec_moving_info[i][0] / 180 * 3.14) *
            circlec_moving_info[i][2];

        float& x = m_dynamic_objects_data.m_dynamic_objects_data[i].color.x;
        float& y = m_dynamic_objects_data.m_dynamic_objects_data[i].color.y;
        float& z = m_dynamic_objects_data.m_dynamic_objects_data[i].color.z;

        auto updColorChannel =
            [time](float& color_channel, float& color_changing_speed)
        {
            color_channel += time * color_changing_speed;
            if (color_channel > 1 || color_channel < 0)
            {
                color_channel = std::clamp(color_channel, 0.f, 1.f);
                color_changing_speed *= -1;
            }
        };

        updColorChannel(x, circlec_color_info[i][0]);
        updColorChannel(y, circlec_color_info[i][1]);
        updColorChannel(z, circlec_color_info[i][2]);
    }
}

void
Scene::create(float width, float height)
{
    // Models
    m_models.resize(3);
    circlec_moving_info.resize(m_models.size());
    circlec_color_info.resize(m_models.size());

    circlec_moving_info[0][0] = 0;
    circlec_moving_info[0][1] = -40;
    circlec_moving_info[0][2] = 2;

    circlec_color_info[0][0] = 1;
    circlec_color_info[0][1] = 0.5;
    circlec_color_info[0][2] = 0.1;
    //////////

    circlec_moving_info[1][0] = 0;
    circlec_moving_info[1][1] = 50;
    circlec_moving_info[1][2] = 4;

    circlec_color_info[1][0] = 0.2;
    circlec_color_info[1][1] = 1;
    circlec_color_info[1][2] = 0.7;
    //////////
    circlec_moving_info[2][0] = 0;
    circlec_moving_info[2][1] = 80;
    circlec_moving_info[2][2] = 1;

    circlec_color_info[2][0] = 0.3;
    circlec_color_info[2][1] = 0.4;
    circlec_color_info[2][2] = 0.5;
    /////////

    Mesh<UniversalVertex> mesh;

    // First Model
    mesh = MESH_FACTORY.createUniversalRectangleMesh({-1, -1}, {0.5, 0.5},
                                                     {0, 0, 1});
    m_models[0].first.setMesh(mesh);
    m_models[0].second = 3;

    // Camera
    m_camera.setAspectRatio(width / height);

    m_mesh_combiner.combine(m_models);

    m_dynamic_objects_data.m_dynamic_objects_data.resize(m_models[0].second);
}

UBO
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
