#ifndef CAMERA_2D_HPP
#define CAMERA_2D_HPP

#include <glm/glm.hpp>

#include "basic_camera.hpp"

namespace kusengine::render
{
class Camera2D : public BasicCamera
{
public:
    Camera2D(uint32_t width = 16, uint32_t height = 9);

    const glm::mat4& recalculate() & override;

    void setViewWidth(float width);

    void processKeyboard(int direction_num, float el_time);

private:
    glm::vec2 m_position;

    float m_zoom;

    float m_view_width;
};
}; // namespace kusengine::render

#endif // CAMERA_2D_HPP
