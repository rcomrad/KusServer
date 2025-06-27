#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace kusengine::render
{

Camera2D::Camera2D()
{
    m_position     = {0.0f, 0.0f};
    m_zoom         = 1.0f;
    m_aspect_ratio = 16.0f / 9.0f;
    m_view_width   = 10.0f;
}

glm::mat4
Camera2D::recalculate()
{
    float view_height = m_view_width / m_aspect_ratio;
    glm::mat4 projection =
        glm::ortho(-m_view_width / 2.0f, m_view_width / 2.0f,
                   -view_height / 2.0f, view_height / 2.0f, -1.0f, 1.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view           = glm::scale(view, glm::vec3(m_zoom, m_zoom, 1.0f));
    view           = glm::translate(view, glm::vec3(-m_position, 0.0f));

    return m_view_projection = projection * view;
}

void
Camera2D::setAspectRatio(float aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
}

glm::mat4
Camera2D::getViewProjection() const
{
    return m_view_projection;
}

void
Camera2D::move(const glm::vec2& offset)
{
    m_position += offset;
}

void
Camera2D::zoom(float factor)
{
    m_zoom *= factor;
}

void
Camera2D::setViewWidth(float width)
{
    m_view_width = width;
}

}; // namespace kusengine
