#include "template_storage.hpp"

#include <exception>
#include <fstream>

#include "utility/file_system/path_storage.hpp"

#include "animal_template.hpp"
#include "block_template.hpp"

using json = nlohmann::json;

namespace kusengine
{

TemplateStorage&
TemplateStorage::getInstance()
{
    static TemplateStorage temp_storage;
    return temp_storage;
}

std::optional<std::pair<std::shared_ptr<Template>, SomeTempararyData>>
TemplateStorage::getTemplate(std::string_view key) const
{
    std::optional<std::pair<std::shared_ptr<Template>, SomeTempararyData>> res;

    auto it = m_template_storage.find(key.data());

    if (it != m_template_storage.end())
    {
        res.emplace(it.operator*().second);
    }

    return res;
}

void
TemplateStorage::loadBlocks(const nlohmann::json_abi_v3_11_3::json& json)
{
    for (auto& [chapter, value] : json.items())
    {
        BlockTemplate block_template;
        block_template.max_hp = value["max_hp"];

        m_template_storage[chapter].first =
            std::make_shared<BlockTemplate>(block_template);

        m_template_storage[chapter].second.texture_name = value["texture"];
    }
}

void
TemplateStorage::loadAnimals(const nlohmann::json_abi_v3_11_3::json& json)
{
    for (auto& [chapter, value] : json.items())
    {
        AnimalTemplate animal_template;
        animal_template.max_hp     = value["max_hp"];
        animal_template.run_speed  = value["run_speed"];
        animal_template.walk_speed = value["walk_speed"];

        m_template_storage[chapter].first =
            std::make_shared<AnimalTemplate>(animal_template);

        m_template_storage[chapter].second.texture_name = value["texture"];
    }
}

void
TemplateStorage::loadData()
{
    std::string filename =
        util::PathStorage::getFolderPath("resource").value().data();

    filename += "objects_data/templates.json";

    std::ifstream file(filename);
    json data = json::parse(file);

    for (auto& [chapter, value] : data["templates"].items())
    {
        if (chapter == "blocks")
        {
            loadBlocks(value);
        }
        else if (chapter == "animals")
        {
            loadAnimals(value);
        }
        // other....
    }
}

}; // namespace kusengine
