#include "scene.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <math.h>
#include <memory>
#include <random>

#include "engine/drawable/rectangle_shape.hpp"
#include "engine/gui/button.hpp"

namespace kusengine
{

void
Scene::updateFrame(SwapChainFrame& frame) const
{
    frame.updateUniformData(m_ubo);
    m_system.updateMBDD(frame);
}

void
Scene::update(float time)
{

    for (int i = 0; i < m_drawables.size(); ++i)
    {
        // m_drawables[0]->setColor({1.f, 1.f, (rand() % 255) / 255.f, 1.f});
        m_drawables[0]->upd();
    }
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
Scene::create(float width, float height)
{
    m_clear_value.setColor(vk::ClearColorValue(0.4f, 0.3f, 0.1f, 1.f));

    m_camera.setAspectRatio(width / height);
    m_camera.recalculate();
    m_ubo.projection = m_camera.getViewProjection();

    // std::cout << "--------------------------\n";
    // std::cout << glm::to_string(m_ubo.projection) << '\n';
    // std::cout << "--------------------------\n";

    //
    m_drawables.emplace_back(
        std::make_shared<Button>(glm::vec2{0.f, 0.f}, glm::vec2{3.f, 1.f}));

    m_drawables.emplace_back(
        std::make_shared<Button>(glm::vec2{0.f, 0.f}, glm::vec2{0.5f, 4.f}));

    m_system.add(m_drawables);
    m_system.generate();
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
    m_system.draw(command_buffer, pipelayout, frame);
}

void
Scene::moveCamera(float x, float y, float z)
{
    m_camera.move({x, y});
    m_camera.zoom(z + 1);

    m_ubo.projection = m_camera.recalculate();
}
}; // namespace kusengine
