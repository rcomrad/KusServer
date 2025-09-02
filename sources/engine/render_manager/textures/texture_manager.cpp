#include "texture_manager.hpp"

#include <fstream>
#include <iostream>

#include "kernel/framework/include_me.hpp"
#include "kernel/utility/file_system/path.hpp"

using json = nlohmann::json;

namespace kusengine::render
{

void
TextureManager::loadTextures(const DescriptorManager& desc_manager)
{

    // Atlases
    auto res_path = KERNEL.getFolderPath("resource");

    std::string filename = res_path;
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
}

void
TextureManager::addTexture(const std::string& file_path,
                           const DescriptorManager& descriptor_manager)
{
    auto texture_name = util::Path::getName(file_path);

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

const Texture* const
TextureManager::getTexture(const std::string& name) const
{
    auto it = m_texture_storage.find(name);
    if (it == m_texture_storage.end())
    {
        throw "cant find in texture_zone_storage\n";
    }

    return &(it->second);
}
}; // namespace kusengine::render
