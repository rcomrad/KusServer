#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "engine/game_objects/templates/animal_template.hpp"

#include "creature.hpp"
#include "walk.hpp"

namespace kusengine
{

struct AnimalCreateArgs
{
    int current_hp;
    Walk walk;

    std::string texture_name;
    glm::vec2 size;
    glm::vec2 position;
};

class Animal final : public Creature
{
public:
    Animal(std::shared_ptr<const AnimalTemplate> temp,
           const AnimalCreateArgs& args);

    void logic() override;

private:
    std::shared_ptr<const AnimalTemplate> m_an_template;

    Walk m_walk;
};
}; // namespace kusengine

#endif // ANIMAL_HPP
