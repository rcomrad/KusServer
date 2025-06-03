#include "rectangle_shape.hpp"

#include "drawable_system.hpp"

namespace kusengine
{

RectangleShape::RectangleShape(const glm::vec2& position, const glm::vec2& size)
    : m_position(position), m_size(size)
{
    setPosition(m_position);
    setSize(m_size);
}

void
RectangleShape::setPosition(const glm::vec2& position)
{
    m_position = position;
}

void
RectangleShape::setSize(const glm::vec2& size)
{
    m_size = size;
}

void
RectangleShape::createBeforeGenerateUnique()
{
    Drawable::create(m_size);
}

}; // namespace kusengine
