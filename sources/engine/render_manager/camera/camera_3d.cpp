#include "camera_3d.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace kusengine::render
{
Camera3D::Camera3D(const glm::vec3& position,
                   const glm::vec3& up,
                   float yaw,
                   float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_movement_speed(2.5f),
      m_mouse_sensitivity(0.1f),
      m_zoom(45.0f)
{
    m_position = position;
    m_world_up = up;
    m_yaw      = yaw;
    m_pitch    = pitch;

    updateCameraVectors();

    m_directions = {
        {GLFW_KEY_A,            Direction::LEFT   },
        {GLFW_KEY_D,            Direction::RIGHT  },
        {GLFW_KEY_S,            Direction::BACK   },
        {GLFW_KEY_W,            Direction::FORWARD},
        {GLFW_KEY_ESCAPE,       Direction::UP     },
        {GLFW_KEY_LEFT_CONTROL, Direction::DOWN   },
    };
}

void
Camera3D::setAspectRatio(float ar)
{
    m_aspect_ratio = ar;
}

glm::mat4
Camera3D::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_zoom), m_aspect_ratio, m_near_plane,
                            m_far_plane) *
           glm::lookAt(m_position, m_position + m_front, m_up);
}

void
Camera3D::processKeyboard(int direction_num, float el_time)
{
    float velocity = m_movement_speed * el_time;

    Direction direction = m_directions[direction_num];

    switch (direction)
    {
        case Direction::RIGHT:
            m_position += velocity * m_right;
            break;
        case Direction::LEFT:
            m_position -= velocity * m_right;
            break;
        case Direction::BACK:
            m_position -= velocity * m_front;
            break;
        case Direction::FORWARD:
            m_position += velocity * m_front;
            break;
        default:
            break;
    }
}

void
Camera3D::processMouseMovement(float x_offset,
                               float y_offset,
                               bool constrain_pitch)
{
    x_offset *= m_mouse_sensitivity;
    y_offset *= m_mouse_sensitivity;

    m_yaw += x_offset;
    m_pitch += y_offset;

    if (constrain_pitch)
    {
        if (m_pitch > 89.0f) m_pitch = 89.0f;
        if (m_pitch < -89.0f) m_pitch = -89.0f;
    }
}

void
Camera3D::processMouseScroll(float yoffset)
{
    m_zoom -= yoffset;
    if (m_zoom < 1.0f) m_zoom = 1.0f;
    if (m_zoom > 90.0f) m_zoom = 90.0f;
}

void
Camera3D::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
} // namespace kusengine::render
