#include "material_manager.hpp"

#include "engine/render_manager/textures/texture_manager.hpp"

#include "texture_material.hpp"
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
    std::unordered_map<std::string, std::unique_ptr<Material>>
        texture_materials;

    texture_materials["water"] = std::make_unique<TextureMaterial>(
        texture_manager.getTextureZone("water"));

    texture_materials["stone"] = std::make_unique<TextureMaterial>(
        texture_manager.getTextureZone("stone"));

    texture_materials["wood"] = std::make_unique<TextureMaterial>(
        texture_manager.getTextureZone("wood"));

    m_materials[Material::Type::TEXTURE] = std::move(texture_materials);
}
} // namespace kusengine::render
