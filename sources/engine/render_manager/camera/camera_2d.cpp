
#include "camera_2d.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace kusengine::render
{

Camera2D::Camera2D(uint32_t width, uint32_t height)
    : BasicCamera(Type::DEFAULT_CAMERA_2D, width, height),
      m_position{0.f, 0.f},
      m_zoom{1.f},
      m_view_width{static_cast<float>(width)}
{
}

const glm::mat4&
Camera2D::recalculate() &
{
    float view_height = m_view_width / m_aspect_ratio;
    glm::mat4 projection =
        glm::ortho(-m_view_width / 2.0f, m_view_width / 2.0f,
                   -view_height / 2.0f, view_height / 2.0f, -1.0f, 1.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view           = glm::scale(view, glm::vec3(m_zoom, m_zoom, 1.0f));
    view           = glm::translate(view, glm::vec3(-m_position, 0.0f));

    return m_matrix = projection * view;
}

void
Camera2D::processKeyboard(int direction_num, float el_time)
{
    float velocity = el_time;

    switch (direction_num)
    {
        case GLFW_KEY_D:
            m_position.x += velocity;
            break;
        case GLFW_KEY_A:
            m_position.x -= velocity;
            break;
        case GLFW_KEY_S:
            m_position.y += velocity;
            break;
        case GLFW_KEY_W:
            m_position.y -= velocity;
            break;
        case GLFW_KEY_UP:
            m_zoom *= (velocity + 1);
            break;
        case GLFW_KEY_DOWN:
            m_zoom /= (velocity + 1);
            if (m_zoom <= 0.1) m_zoom = 0.1;
            break;
        default:
            break;
    }
}

void
Camera2D::setViewWidth(float width)
{
    m_view_width = width;
}

}; // namespace kusengine::render
