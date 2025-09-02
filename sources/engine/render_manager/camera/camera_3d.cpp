#include "camera_3d.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace kusengine::render
{

glm::vec3 Camera3D::m_world_up = glm::vec3(0.f, 1.f, 0.f);

Camera3D::Camera3D(uint32_t width, uint32_t height)
    : BasicCamera(Type::DEFAULT_CAMERA_3D, width, height),
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_movement_speed(2.5f),
      m_zoom(45.0f),
      m_position{0.f, 0.f, 3.f},
      m_yaw{-90.f},
      m_pitch{0.f}
{
    recalculate();
}

void
Camera3D::processKeyboard(int direction_num, float el_time)
{
    float velocity = m_movement_speed * el_time * 4;

    switch (direction_num)
    {
        case GLFW_KEY_D:
            m_position += velocity * m_right;
            break;
        case GLFW_KEY_A:
            m_position -= velocity * m_right;
            break;
        case GLFW_KEY_S:
            m_position -= velocity * m_front;
            break;
        case GLFW_KEY_W:
            m_position += velocity * m_front;
            break;
        case GLFW_KEY_SPACE:
            m_position.y -= velocity * 3;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            m_position.y += velocity * 3;
            break;
        default:
            break;
    }
}

void
Camera3D::processMouseMovement(const glm::dvec2& offset)
{

    m_yaw += offset.x;
    m_pitch += offset.y;

    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
}

const glm::mat4&
Camera3D::recalculate() &
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up    = glm::normalize(glm::cross(m_right, m_front));

    return m_matrix = glm::perspective(glm::radians(m_zoom), m_aspect_ratio,
                                       m_near_plane, m_far_plane) *
                      glm::lookAt(m_position, m_position + m_front, m_up);
}
} // namespace kusengine::render
