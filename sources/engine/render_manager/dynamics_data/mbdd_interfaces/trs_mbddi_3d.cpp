#include "trs_mbddi_3d.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace kusengine
{
namespace render
{

TRS_MBDDI_3D::TRS_MBDDI_3D()
{
    updModelMatrix();
}

void
TRS_MBDDI_3D::updModelMatrix()
{
    m_data->model = translate * rotate * scale;
}

void
TRS_MBDDI_3D::setRotation(float angle)
{
    rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void
TRS_MBDDI_3D::setSize(float size_x, float size_y, float size_z)
{
    scale = glm::scale(glm::mat4(1.0f), glm::vec3(size_x, size_y, size_z));
}

void
TRS_MBDDI_3D::setSize(const glm::vec3& size)
{
    setSize(size.x, size.y, size.z);
}

void
TRS_MBDDI_3D::setPosition(float pos_x, float pos_y, float pos_z)
{
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(pos_x, pos_y, pos_z));
}

void
TRS_MBDDI_3D::setPosition(const glm::vec3& position)
{
    setPosition(position.x, position.y, position.z);
}

void
TRS_MBDDI_3D::setColor(const glm::vec4& color)
{
    m_data->color = color;
}

void
TRS_MBDDI_3D::setColor(float r, float g, float b, float a)
{
    setColor({r, g, b, a});
}
}; // namespace render
}; // namespace kusengine
