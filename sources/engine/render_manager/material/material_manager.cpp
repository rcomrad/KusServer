#include "material_manager.hpp"

#include "engine/parsers/material_parser.hpp"
#include "engine/render_manager/textures/texture_manager.hpp"
#include "kernel/framework/include_me.hpp"

#include "texture_zone_material.hpp"

namespace kusengine::render
{

const Material* const
MaterialManager::getMaterial(const std::string& name) const
{
    return m_materials.at(name).get();
}

// TODO: Builder pattern
void
MaterialManager::setup(const TextureManager& texture_manager)
{
    parser::MaterialParser parser;

    auto&& path = KERNEL.getFolderPath("resource") + "material.json";

    parser.parse(path, *this, texture_manager);
}

void
MaterialManager::setTextureZones(
    std::unordered_map<std::string, std::unique_ptr<Material>>&& texture_zones)
{
    for (auto&& tz : texture_zones)
    {
        if (m_materials.find(tz.first) != m_materials.end())
        {
            throw std::exception("naming differnet material by one name");
        }
        m_materials.emplace(std::move(tz));
    }
}

} // namespace kusengine::render
