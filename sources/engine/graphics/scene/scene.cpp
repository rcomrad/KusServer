#include "scene.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <math.h>
#include <memory>
#include <random>

#include "engine/game_objects/block.hpp"
#include "engine/graphics/drawable/rectangle_shape.hpp"
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
Scene::update(float elapsed_time)
{
    m_game_objects_storage.update(elapsed_time);
}

void
Scene::create(float width, float height)
{
    m_clear_value.setColor(vk::ClearColorValue(0.4f, 0.3f, 0.1f, 1.f));

    m_camera.setAspectRatio(width / height);
    m_camera.recalculate();
    m_ubo.projection = m_camera.getViewProjection();

    // -- camera init end -- //

    m_game_objects_storage.loadData("objects_data/game_objects.json");

    m_game_objects_storage.pushToDrawableSystem(m_system);

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
