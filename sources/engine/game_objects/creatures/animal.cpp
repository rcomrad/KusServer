#include "animal.hpp"

namespace kusengine
{
Animal::Animal(std::shared_ptr<const AnimalTemplate> temp,
               const AnimalCreateArgs& args)
    : Creature(args.current_hp, args.position), m_walk(args.walk)
{
    m_an_template = temp;
    setSize(args.size);

    m_shape->loadTexture(args.texture_name);
}
void
Animal::logic(float elapsed_time)
{
    m_walk.walk([this](float x, float y) { this->setPosition(x, y); },
                m_position, m_an_template->walk_speed, elapsed_time);

    updModelMatrix();
}
}; // namespace kusengine
