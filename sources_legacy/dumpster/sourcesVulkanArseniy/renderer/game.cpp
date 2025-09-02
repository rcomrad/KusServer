#include "game.hpp"

internal Entity*
create_entity(GameState* gameState, Transform transform)
{
    Entity* e = 0;

    if (gameState->entityCount < MAX_ENTITIES)
    {
        e = &gameState->entities[gameState->entityCount++];

        e->transform = transform;
    }

    return e;
}

bool
init_game(GameState* gameState)
{
    create_entity(gameState, {1 * 120.0f, 1 * 60.0f, 70.0f, 70.0f});

    return true;
}

void
update_game(GameState* gameState, float x, float y)
{

    Entity* e = &gameState->entities[0];
    e->transform.xPos += x;
    e->transform.yPos += y;
}