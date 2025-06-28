#include "trs_mbddi.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace kusengine
{
namespace render
{

TRS_MBDDI::TRS_MBDDI()
{
    updModelMatrix();
}

void
TRS_MBDDI::updModelMatrix()
{
    m_data->model = translate * rotate * scale;
}

void
TRS_MBDDI::setRotation(float angle)
{
    rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void
TRS_MBDDI::setSize(float size_x, float size_y)
{
    scale = glm::scale(glm::mat4(1.0f), glm::vec3(size_x, size_y, 1));
}

void
TRS_MBDDI::setSize(const glm::vec2& size)
{
    setSize(size.x, size.y);
}

void
TRS_MBDDI::setPosition(float pos_x, float pos_y)
{
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(pos_x, pos_y, 0.f));
}

void
TRS_MBDDI::setPosition(const glm::vec2& position)
{
    setPosition(position.x, position.y);
}

void
TRS_MBDDI::setColor(const glm::vec4& color)
{
    m_data->color = color;
}

void
TRS_MBDDI::setColor(float r, float g, float b, float a)
{
    setColor({r, g, b, a});
}
}; // namespace render
}; // namespace kusengine
