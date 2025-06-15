#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "engine/game_objects/game_object.hpp"

namespace kusengine
{
class Creature : public GameObject
{
public:
    Creature(int current_hp, const glm::vec2& pos);

protected:
    int m_current_hp;

    glm::vec2 m_position;

    // animation
};
}; // namespace kusengine

#endif // CREATURE_HPP
