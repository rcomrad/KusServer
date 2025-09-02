#ifndef CAMERA_3D_HPP
#define CAMERA_3D_HPP

#include <glm/glm.hpp>

#include <unordered_map>

#include "basic_camera.hpp"

namespace kusengine::render
{
class Camera3D : public BasicCamera
{
public:
    Camera3D(uint32_t width = 16, uint32_t height = 9);

    const glm::mat4& recalculate() & override;

    void processKeyboard(int direction_num, float el_time);

    void processMouseMovement(const glm::dvec2& offset);

private:
    static glm::vec3 m_world_up;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    float m_yaw;
    float m_pitch;

    // settings
    float m_movement_speed = 0.5f;
    float m_zoom           = 45.0f;
    float m_near_plane     = 0.1f;
    float m_far_plane      = 50.0f;
};
}; // namespace kusengine::render

#endif // CAMERA_3D_HPP
