#include "button.hpp"

#include "engine/drawable/rectangle_shape.hpp"
namespace kusengine
{

Button::Button(const glm::vec2& position, const glm::vec2& size)
    : Drawable(RectangleShape())
{
    setPosition(position.x, position.y);
    setSize(size.x, size.y);
    m_shape->loadTexture("button.png");
}

}; // namespace kusengine
