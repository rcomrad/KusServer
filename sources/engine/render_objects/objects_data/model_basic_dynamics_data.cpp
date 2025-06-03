#include "model_basic_dynamics_data.hpp"

#include "glm/gtc/matrix_transform.hpp"
namespace kusengine
{

glm::vec2 ModelBasicDynamicsDataInterface::m_window_size = {0, 0};

void
ModelBasicDynamicsDataInterface::setWindowSize(float x, float y)
{
    m_window_size.x = x;
    m_window_size.y = y;
}

void
ModelBasicDynamicsDataInterface::linkData(MBDD* data)
{
    m_data = data;
}

void
ModelBasicDynamicsDataInterface::setRotation(float angle)
{
    m_data->rotation =
        glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void
ModelBasicDynamicsDataInterface::setScale(float scale_x,
                                          float scale_y,
                                          bool is_0_1_range)
{
    if (is_0_1_range == false)
    {
        scale_x /= m_window_size.x;
        scale_y /= m_window_size.y;
    }
    m_data->scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale_x, scale_y, 1));
}

void
ModelBasicDynamicsDataInterface::setScale(const glm::vec2& scale,
                                          bool is_0_1_range)
{
    setScale(scale.x, scale.y, is_0_1_range);
}

void
ModelBasicDynamicsDataInterface::setPosition(float pos_x,
                                             float pos_y,
                                             bool is_0_1_range)
{
    if (is_0_1_range == false)
    {
        pos_x /= m_window_size.x;
        pos_y /= m_window_size.y;
    }
    m_data->translation =
        glm::translate(glm::mat4(1.0f), glm::vec3(pos_x, pos_y, 1.f));
}

void
ModelBasicDynamicsDataInterface::setPosition(const glm::vec2& position,
                                             bool is_0_1_range)
{
    setScale(position.x, position.y, is_0_1_range);
}

void
ModelBasicDynamicsDataInterface::setColor(const glm::vec4& color,
                                          bool is_0_1_range)
{
    m_data->color = color;

    if (is_0_1_range == false)
    {
        m_data->color /= 255.f;
    }
}

void
ModelBasicDynamicsDataInterface::setColor(float r,
                                          float g,
                                          float b,
                                          float a,
                                          bool is_0_1_range)
{
    setColor({r, g, b, a}, is_0_1_range);
}

}; // namespace kusengine
