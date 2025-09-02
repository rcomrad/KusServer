#ifndef GAME_HPP
#define GAME_HPP

#include "defines.h"
#include "shared_render_types.hpp"

uint32_t constexpr MAX_ENTITIES = 100;

struct Entity
{
    Transform transform;
};

struct GameState
{
    uint32_t entityCount = 0;
    Entity entities[MAX_ENTITIES];
};

internal Entity*
create_entity(GameState* gameState, Transform transform);

bool
init_game(GameState* gameState);

void
update_game(GameState* gameState, float x, float y);

#endif // GAME_HPP