#include "material_manager.hpp"

#include "engine/parsers/material_parser.hpp"
#include "engine/render_manager/textures/texture_manager.hpp"
#include "kernel/framework/include_me.hpp"

#include "texture_zone_material.hpp"

namespace kusengine::render
{

const Material* const
MaterialManager::getMaterial(Material::Type mtype,
                             const std::string& name) const
{
    auto it = m_materials.find(mtype);

    if (it == m_materials.end())
    {
        throw std::exception("dind not find material type");
    }
    auto it_m = it->second.find(name);

    if (it_m == it->second.end())
    {
        throw std::exception("dind not find material");
    }

    return it_m->second.get();
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
    m_materials[Material::Type::TEXTURE_ZONE] = std::move(texture_zones);
}

} // namespace kusengine::render
