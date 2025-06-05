#include "model_basic_dynamics_data.hpp"

#include "glm/gtc/matrix_transform.hpp"
namespace kusengine
{

ModelBasicDynamicsDataInterface::ModelBasicDynamicsDataInterface(
    const ModelBasicDynamicsDataInterface& other)
{
    m_data    = new MBDD();
    *m_data   = *other.m_data;
    is_linked = false;

    translate = other.translate;
    rotate    = other.rotate;
    scale     = other.scale;
}

ModelBasicDynamicsDataInterface::ModelBasicDynamicsDataInterface(
    ModelBasicDynamicsDataInterface&& other)
{
    m_data       = other.m_data;
    other.m_data = nullptr;
    is_linked    = other.is_linked;

    translate = std::move(other.translate);
    rotate    = std::move(other.rotate);
    scale     = std::move(other.scale);
}

ModelBasicDynamicsDataInterface&
ModelBasicDynamicsDataInterface::operator=(
    const ModelBasicDynamicsDataInterface& other)
{
    m_data    = new MBDD();
    *m_data   = *other.m_data;
    is_linked = false;

    translate = other.translate;
    rotate    = other.rotate;
    scale     = other.scale;

    return *this;
}
ModelBasicDynamicsDataInterface&
ModelBasicDynamicsDataInterface::operator=(
    ModelBasicDynamicsDataInterface&& other)
{
    m_data       = other.m_data;
    other.m_data = nullptr;
    is_linked    = other.is_linked;

    translate = std::move(other.translate);
    rotate    = std::move(other.rotate);
    scale     = std::move(other.scale);
    return *this;
}

MBDD::MBDD() : color(1.f, 1.f, 1.f, 1.f)
{
}

ModelBasicDynamicsDataInterface::ModelBasicDynamicsDataInterface()
    : translate(1.f), rotate(1.f), scale(1.f)
{
    m_data = new MBDD();

    is_linked = false;
}

ModelBasicDynamicsDataInterface::~ModelBasicDynamicsDataInterface()
{
    if (is_linked == false) delete m_data;
}

void
ModelBasicDynamicsDataInterface::upd()
{
    m_data->model = translate * rotate * scale;
}

void
ModelBasicDynamicsDataInterface::linkData(MBDD* data)
{
    if (data != m_data)
    {
        *data = *m_data;

        if (is_linked == false)
        {
            delete m_data;
        }

        m_data    = data;
        is_linked = true;
    }
}

void
ModelBasicDynamicsDataInterface::setRotation(float angle)
{
    rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void
ModelBasicDynamicsDataInterface::setSize(float size_x, float size_y)
{
    scale = glm::scale(glm::mat4(1.0f), glm::vec3(size_x, size_y, 1));
}

void
ModelBasicDynamicsDataInterface::setSize(const glm::vec2& size)
{
    setSize(size.x, size.y);
}

void
ModelBasicDynamicsDataInterface::setPosition(float pos_x, float pos_y)
{
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(pos_x, pos_y, 0.f));
}

void
ModelBasicDynamicsDataInterface::setPosition(const glm::vec2& position)
{
    setPosition(position.x, position.y);
}

void
ModelBasicDynamicsDataInterface::setColor(const glm::vec4& color)
{
    m_data->color = color;
}

void
ModelBasicDynamicsDataInterface::setColor(float r, float g, float b, float a)
{
    setColor({r, g, b, a});
}

}; // namespace kusengine
