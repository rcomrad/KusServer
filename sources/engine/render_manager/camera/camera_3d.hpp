#ifndef CAMERA_3D_HPP
#define CAMERA_3D_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <unordered_map>

#include "help_enums.hpp"

namespace kusengine::render
{
class Camera3D
{
public:
    Camera3D(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
             const glm::vec3& up       = glm::vec3(0.0f, 1.0f, 0.0f),
             float yaw                 = -90.0f,
             float pitch               = 0.0f);

    void setAspectRatio(float ar);

    glm::mat4 getProjectionMatrix() const;

    void processKeyboard(int direction_num, float el_time);
    void processMouseMovement(float x_offset,
                              float y_offset,
                              bool constrain_pitch = true);

    void processMouseScroll(float yoffset);

    void updateCameraVectors();

private:
    std::unordered_map<int, Direction> m_directions;

    float m_aspect_ratio;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;

    float m_yaw;
    float m_pitch;

    // settings
    float m_movement_speed    = 0.5f;
    float m_mouse_sensitivity = 0.1f;
    float m_zoom              = 45.0f;
    float m_near_plane        = 0.1f;
    float m_far_plane         = 100.0f;
};
}; // namespace kusengine::render

#endif // CAMERA_3D_HPP
