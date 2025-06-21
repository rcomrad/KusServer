#include "universal_mbddi.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace kusengine
{
namespace render
{
void
UniversalMBDDI::updModelMatrix()
{
    m_data->model = translate * rotate * scale;
}

void
UniversalMBDDI::setRotation(float angle)
{
    rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void
UniversalMBDDI::setSize(float size_x, float size_y)
{
    scale = glm::scale(glm::mat4(1.0f), glm::vec3(size_x, size_y, 1));
}

void
UniversalMBDDI::setSize(const glm::vec2& size)
{
    setSize(size.x, size.y);
}

void
UniversalMBDDI::setPosition(float pos_x, float pos_y)
{
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(pos_x, pos_y, 0.f));
}

void
UniversalMBDDI::setPosition(const glm::vec2& position)
{
    setPosition(position.x, position.y);
}

void
UniversalMBDDI::setColor(const glm::vec4& color)
{
    m_data->color = color;
}

void
UniversalMBDDI::setColor(float r, float g, float b, float a)
{
    setColor({r, g, b, a});
}
}; // namespace render
}; // namespace kusengine
