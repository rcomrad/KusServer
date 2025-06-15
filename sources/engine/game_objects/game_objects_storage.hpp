#ifndef GAME_OBJECTS_LOADER_HPP
#define GAME_OBJECTS_LOADER_HPP

#include <nlohmann/json.hpp>

#include "engine/game_objects/game_object.hpp"

namespace kusengine
{

class DrawableSystem;

class GameObjectsStorage
{
public:
    GameObjectsStorage() = default;

    void loadData(std::string filename);

    void pushToDrawableSystem(DrawableSystem& dr_system);

private:
    void loadBlocks(const nlohmann::json_abi_v3_11_3::json& objects);
    void loadAnimals(const nlohmann::json_abi_v3_11_3::json& objects);

    std::vector<std::shared_ptr<GameObject>> m_game_objects_storage;
};
}; // namespace kusengine

#endif // GAME_OBJECTS_LOADER_HPP
