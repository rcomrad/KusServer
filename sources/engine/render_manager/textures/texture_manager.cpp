#include "texture_manager.hpp"

#include <fstream>
#include <iostream>

#include "engine/json_parser/model_2d_parser.hpp"
#include "utility/file_system/path_storage.hpp"

using json = nlohmann::json;

namespace kusengine::render
{

void
TextureManager::loadTextures(const DescriptorManager& desc_manager)
{

    // Atlases
    auto res_path = util::PathStorage::getFolderPath("resource").value();

    std::string filename = res_path.data();
    filename += "engine_textures/texture_paths.json";

    std::ifstream file(filename);
    json data = json::parse(file);

    std::vector<std::string> paths = data["texture_paths"];

    for (auto& path : paths)
    {
        addTexture(
            std::format("{}{}{}", res_path.data(), "engine_textures/", path),
            desc_manager);
    }

    // Zones

    auto textures_data = json_parser::parseTextures();

    for (auto& texture_data : textures_data)
    {
        m_texture_zone_storage[texture_data.name].m_texture =
            &m_texture_storage[texture_data.filename];

        m_texture_zone_storage[texture_data.name].m_scale =
            texture_data.scale;

        m_texture_zone_storage[texture_data.name].m_size = texture_data.size;
    }
}

void
TextureManager::addTexture(const std::string& file_path,
                           const DescriptorManager& descriptor_manager)
{

    std::string texture_name = util::Path::getName(file_path, LOCAL_CONTEXT);

    if (m_texture_storage.contains(texture_name))
    {
        std::cerr << texture_name << " has already been added\n";
        return;
    }
    try
    {
        Texture new_texture;
        new_texture.loadTexture(file_path);

        new_texture.allocDescriptorSet(descriptor_manager);

        m_texture_storage[texture_name] = std::move(new_texture);
    }
    catch (std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
        return;
    }
}

const TextureZone* const
TextureManager::getTextureZone(const std::string& name) const
{
    auto it = m_texture_zone_storage.find(name);
    if (it == m_texture_zone_storage.end())
    {
        std::cout << name << " cant find in texture_zone_storage\n";

        return &(m_texture_zone_storage.begin()->second);
    }

    return &(it->second);
}
}; // namespace kusengine::render
