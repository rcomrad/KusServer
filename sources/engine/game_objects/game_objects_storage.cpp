#include "game_objects_storage.hpp"

#include <fstream>
#include <iostream>

#include "creatures/animal.hpp"
#include "engine/game_objects/templates/template_storage.hpp"
#include "engine/graphics/drawable/drawable_system.hpp"
#include "utility/file_system/path_storage.hpp"

#include "block.hpp"

using json = nlohmann::json;

namespace kusengine
{

void
GameObjectsStorage::loadBlocks(const nlohmann::json_abi_v3_11_3::json& objects)
{
    BlockCreateArgs args{};
    for (auto& obj : objects)
    {
        std::string type = obj["type"];
        args.position    = {obj["position"]["x"], obj["position"]["y"]};
        args.size        = {obj["size"]["x"], obj["size"]["y"]};
        args.current_hp  = obj["current_hp"];

        auto type_template = TEMPLATE_STORAGE.getTemplate(type);

        if (type_template.has_value() == false)
        {
            std::cout << "Failed find template";
            continue;
        }
        args.texture_name = type_template.value().second.texture_name;

        m_game_objects_storage.emplace_back(std::make_shared<Block>(
            std::static_pointer_cast<kusengine::BlockTemplate>(
                type_template.value().first),
            args));
    }
}

void
GameObjectsStorage::loadAnimals(const nlohmann::json_abi_v3_11_3::json& objects)
{
    AnimalCreateArgs args{};

    for (auto& obj : objects)
    {
        std::string type = obj["type"];
        args.position    = {obj["position"]["x"], obj["position"]["y"]};
        args.size        = {obj["size"]["x"], obj["size"]["y"]};
        args.current_hp  = obj["current_hp"];

        std::vector<Walk::StopInfo> stops_info;
        objects["walk"].size(); // ?
        // stops_info.reserve();
        for (auto& stop : objects["walk"])
        {
            glm::vec2 pos = {stop["position"]["x"], stop["position"]["y"]};
            float t       = stop["wait_time"];
            stops_info.emplace_back(Walk::StopInfo{pos, t});
        }
        args.walk.setInfo(stops_info);

        auto type_template = TEMPLATE_STORAGE.getTemplate(type);

        if (type_template.has_value() == false)
        {
            std::cout << "Failed find template";
            continue;
        }
        args.texture_name = type_template.value().second.texture_name;

        m_game_objects_storage.emplace_back(std::make_shared<Animal>(
            std::static_pointer_cast<kusengine::AnimalTemplate>(
                type_template.value().first),
            args));
    }
}

void
GameObjectsStorage::loadData(std::string filename)
{
    filename =
        util::PathStorage::getFolderPath("resource").value().data() + filename;

    std::ifstream file(filename);
    json data = json::parse(file);

    for (auto& [chapter_name, objects] : data["game_objects"].items())
    {
        if (chapter_name == "blocks")
        {
            loadBlocks(objects);
        }
        else if (chapter_name == "animals")
        {
            loadAnimals(objects);
        }
    }
}

void
GameObjectsStorage::pushToDrawableSystem(DrawableSystem& dr_system)
{
    dr_system.setDrawableVector(m_game_objects_storage);
}

}; // namespace kusengine
