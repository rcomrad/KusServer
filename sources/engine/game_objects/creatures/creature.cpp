#include "creature.hpp"

#include "engine/graphics/drawable/rectangle_shape.hpp"
namespace kusengine
{
Creature::Creature(int current_hp, const glm::vec2& pos)
    : GameObject(RectangleShape()), m_current_hp(current_hp)
{
    m_position = pos;
    setPosition(m_position);
}

}; // namespace kusengine
