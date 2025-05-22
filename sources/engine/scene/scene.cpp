#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <math.h>

#include "engine/render_objects/model/mesh/mesh_factory.hpp"

namespace kusengine
{

void
Scene::updateFrame(SwapChainFrame& frame) const
{
    frame.updateUniformData(m_ubo);
    frame.updateObjectsDynamicData(m_model_storage.objDynData());
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

    RenderObject render_object(MESH_FACTORY.createUniversalRectangleMesh(
                                   {0, 0}, {0.7, 0.5}, {0.f, 1.f, 1.f}),
                               cat_texture.value());

    m_model_storage.addRenderObject(render_object);

    render_object.setDynamicsData({1.f, 1.f, 1.f});

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
              const vk::PipelineLayout& pipelayout) const
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
