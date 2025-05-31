#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <math.h>
#include <memory>
#include <random>

#include "engine/render_objects/model/mesh/mesh_factory.hpp"

namespace kusengine
{

void
Scene::updateFrame(SwapChainFrame& frame) const
{
    frame.updateUniformData(m_ubo);
    frame.updateObjectsDynamicData(m_model_storage.objDynamicData());
}

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
Scene::create(float width, float height, const TextureStorage& texture_storage)
{
    m_clear_value.setColor(vk::ClearColorValue(0.4f, 0.3f, 0.1f, 1.f));

    m_camera.setAspectRatio(width / height);
    m_camera.recalculate();
    m_ubo.projection = m_camera.getViewProjection();

    auto cat_texture = texture_storage.getTexture("cat.png");
    if (cat_texture.has_value() == false)
    {
        std::cout << "Failed get cat.png texture\n";
        return;
    }
    auto eye_texture = texture_storage.getTexture("eye.png");
    if (eye_texture.has_value() == false)
    {
        std::cout << "Failed get eye.png texture\n";
        return;
    }
    auto zvezda_texture = texture_storage.getTexture("zvezda.png");
    if (zvezda_texture.has_value() == false)
    {
        std::cout << "Failed get zvezda.png texture\n";
        return;
    }

    m_render_objects.emplace_back(
        std::make_shared<const Mesh>(
            MESH_FACTORY.createUniversalRectangleMesh({0.f, 0.f}, {2.f, 1.f})),
        cat_texture.value());

    m_render_objects.emplace_back(
        std::make_shared<const Mesh>(
            MESH_FACTORY.createUniversalRectangleMesh({0.f, 0.f}, {1.f, 3.f})),
        eye_texture.value());

    m_render_objects.emplace_back(
        std::make_shared<const Mesh>(
            MESH_FACTORY.createUniversalRectangleMesh({0.f, 0.f}, {1.f, 1.f})),
        cat_texture.value());

    m_render_objects.emplace_back(
        std::make_shared<const Mesh>(MESH_FACTORY.createUniversalTriangleMesh(
            {0.f, 0.f}, {1.f, 2.f}, {-1.f, 2.f})),
        eye_texture.value());

    int vec_size = 4 + 100000;
    m_render_objects.reserve(vec_size);

    auto star_mesh = std::make_shared<const Mesh>(
        MESH_FACTORY.createUniversalRectangleMesh({0.f, 0.f}, {1.f, 2.f}));

    for (int i = 0; i < vec_size; ++i)
    {
        m_render_objects.emplace_back(star_mesh, zvezda_texture.value());
    }

    for (int i = 0; i < m_render_objects.size(); ++i)
    {
        m_model_storage.addRenderObject(m_render_objects[i]);

        m_render_objects[i].setDynamicsData({
            {float(rand() % 255) / 255.f, float(rand() % 255) / 255.f,
             float(rand() % 255) / 255.f},

            {float(rand() % 1000), float(rand() % 1000)}
        });
    }
    m_model_storage.fillBuffers();
}

const UBO&
Scene::ubo() const
{
    return m_ubo;
}

const vk::ClearValue&
Scene::clearColor() const
{
    return m_clear_value;
}

void
Scene::render(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout,
              SwapChainFrame& frame) const
{
    m_model_storage.bind(command_buffer);

    m_model_storage.draw(command_buffer, pipelayout);
}

void
Scene::moveCamera(float x, float y, float z)
{
    m_camera.move({x, y});
    m_camera.zoom(z + 1);

    m_ubo.projection = m_camera.recalculate();
}
}; // namespace kusengine
