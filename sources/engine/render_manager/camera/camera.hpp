#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

namespace kusengine::render
{
class Camera2D
{
public:
    Camera2D();

    void move(const glm::vec2& offset);

    void zoom(float factor);

    void setViewWidth(float width);

    glm::mat4 getViewProjection() const;

    glm::mat4 recalculate();

    void setAspectRatio(float aspect_ratio);

private:
    glm::mat4 m_view_projection;

    glm::vec2 m_position;
    float m_zoom;
    float m_aspect_ratio;
    float m_view_width;
};
}; // namespace kusengine::render

#endif // CAMERA_HPP
