#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <math.h>

#include "engine/model/mesh/mesh_factory.hpp"

namespace kusengine
{

void
Scene::update(float time)
{
    // for (int i = 0; i < m_dynamic_objects_data.size(); ++i)
    // {
    //     m_dynamic_objects_data[i].position = {1, 1};
    //     m_dynamic_objects_data[i].color    = {1, 1, 1};
    // circlec_moving_info[i][0] += circlec_moving_info[i][1] * time;

    // m_dynamic_objects_data[i].position.x =
    //     std::cos(circlec_moving_info[i][0] / 180 * 3.14) *
    //     circlec_moving_info[i][2];

    // m_dynamic_objects_data[i].position.y =
    //     std::sin(circlec_moving_info[i][0] / 180 * 3.14) *
    //     circlec_moving_info[i][2];

    // float& x = m_dynamic_objects_data[i].color.x;
    // float& y = m_dynamic_objects_data[i].color.y;
    // float& z = m_dynamic_objects_data[i].color.z;

    // auto updColorChannel =
    //     [time](float& color_channel, float& color_changing_speed)
    // {
    //     color_channel += time * color_changing_speed;
    //     if (color_channel > 1 || color_channel < 0)
    //     {
    //         color_channel = std::clamp(color_channel, 0.f, 1.f);
    //         color_changing_speed *= -1;
    //     }
    // };

    // updColorChannel(x, circlec_color_info[i][0]);
    // updColorChannel(y, circlec_color_info[i][1]);
    // updColorChannel(z, circlec_color_info[i][2]);
    // }
}

void
Scene::create(float width,
              float height,
              const TextureStorage& texture_storage_ptr)
{
    m_clear_value.setColor(vk::ClearColorValue(0.f, 0.f, 0.f, 1.f));

    // Models
    m_models.resize(2);

    // circlec_moving_info.resize(3);
    // circlec_color_info.resize(3);
    // circlec_moving_info[0][0] = 0;
    // circlec_moving_info[0][1] = -40;
    // circlec_moving_info[0][2] = 2;
    // circlec_color_info[0][0]  = 1;
    // circlec_color_info[0][1]  = 0.5;
    // circlec_color_info[0][2]  = 0.1;
    // //////////
    // circlec_moving_info[1][0] = 0;
    // circlec_moving_info[1][1] = 50;
    // circlec_moving_info[1][2] = 4;
    // circlec_color_info[1][0]  = 0.2;
    // circlec_color_info[1][1]  = 1;
    // circlec_color_info[1][2]  = 0.7;
    // //////////
    // circlec_moving_info[2][0] = 0;
    // circlec_moving_info[2][1] = 80;
    // circlec_moving_info[2][2] = 1;
    // circlec_color_info[2][0]  = 0.3;
    // circlec_color_info[2][1]  = 0.4;
    // circlec_color_info[2][2]  = 0.5;
    /////////

    // First Model
    Mesh mesh2;
    mesh2 = MESH_FACTORY.createUniversalRectangleMesh({0.8, 1.5}, {0.9, 0.5},
                                                      {1, 1, 1});
    m_models[0].first.setMesh(mesh2);
    m_models[0].second = 5;
    m_models[0].first.setTexture(texture_storage_ptr.getTexture("eye.png"));

    // Second Model
    Mesh mesh1;
    mesh1 = MESH_FACTORY.createUniversalRectangleMesh({-1, -1}, {0.5, 0.5},
                                                      {0, 0, 1});
    m_models[1].first.setMesh(mesh1);
    m_models[1].second = 3;
    m_models[1].first.setTexture(texture_storage_ptr.getTexture("cat.png"));

    // Dynamic Data

    m_dynamic_objects_data.resize(m_models[0].second + m_models[1].second);
    for (int i = 0; i < m_models[0].second; ++i)
    {
        m_dynamic_objects_data[i].position = {1 * i, 1};
        m_dynamic_objects_data[i].color    = {1, 1, 1};
    }
    for (int i = m_models[0].second; i < m_models[1].second; ++i)
    {
        m_dynamic_objects_data[i].position = {1 * i, -1};
        m_dynamic_objects_data[i].color    = {1, 1, 1};
    }

    // Camera
    m_camera.setAspectRatio(width / height);
    m_ubo.projection = m_camera.recalculate();
    ///////////////

    m_mesh_combiner.combine(m_models);
}

const UBO&
Scene::ubo() const
{
    return m_ubo;
}

const std::vector<DynamicObjectData>&
Scene::dynamicObjectsData() const
{
    return m_dynamic_objects_data;
}

const vk::ClearValue&
Scene::clearColor() const
{
    return m_clear_value;
}

void
Scene::render(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const
{
    m_mesh_combiner.bindBuffers(command_buffer);

    for (int i = 0; i < m_models.size(); ++i)
    {
        command_buffer.bindDescriptorSets(
            vk::PipelineBindPoint::eGraphics, pipelayout, 1u, 1,
            &(m_models[i].first.getTextureDescriptorSet()), 0, nullptr);

        m_mesh_combiner.draw(command_buffer, i);
    }
}

// void
// Scene::fillDescriptorSets(std::vector<vk::DescriptorSet>& d_sets) const
// {
//     d_sets.emplace_back(
//         m_texture_storage_ptr->getTexture("cat").getDescriptorSet());
// }

void
Scene::moveCamera(float x, float y, float z)
{
    m_camera.move({x, y});
    m_camera.zoom(z + 1);

    m_ubo.projection = m_camera.recalculate();
}
}; // namespace kusengine
