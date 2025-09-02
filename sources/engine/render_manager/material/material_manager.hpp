#ifndef MATERIAL_MANAGER_HPP
#define MATERIAL_MANAGER_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "engine/render_manager/textures/texture_manager.hpp"

#include "material.hpp"

namespace kusengine::render
{

class MaterialManager
{
public:
    void setup(const TextureManager& texture_manager);

    const Material* const getMaterial(Material::Type mtype,
                                      const std::string& name) const;

    void setTextureZones(
        std::unordered_map<std::string, std::unique_ptr<Material>>&&
            texture_zones);

private:
    std::unordered_map<
        Material::Type,
        std::unordered_map<std::string, std::unique_ptr<Material>>>
        m_materials;
};
} // namespace kusengine::render

#endif // MATERIAL_MANAGER_HPP
