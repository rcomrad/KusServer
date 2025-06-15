#ifndef ANIMAL_TEMPLATE_HPP
#define ANIMAL_TEMPLATE_HPP

#include "template.hpp"

namespace kusengine
{
struct AnimalTemplate : Template
{
    int max_hp;
    float run_speed;
    float walk_speed;
};
}; // namespace kusengine

#endif // ANIMAL_TEMPLATE_HPP