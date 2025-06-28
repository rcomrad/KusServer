#include "texture_manager.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

#include "utility/file_system/path_storage.hpp"

using json = nlohmann::json;

namespace kusengine::render
{

void
TextureManager::loadTextures(std::string filename,
                             const DescriptorManager& desc_manager)
{
    auto res_path = util::PathStorage::getFolderPath("resource").value();

    filename = res_path.data() + filename;

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

        new_texture.allocDescriptorSet("default_fragment_shader",
                                       descriptor_manager);

        m_texture_storage[texture_name] = std::move(new_texture);
    }
    catch (std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
        return;
    }
}

const Texture* const
TextureManager::getTexture(const std::string& key) const
{
    auto it = m_texture_storage.find(key);
    if (it == m_texture_storage.end())
    {
        std::cout << key << " cant find in texture storage\n";

        return &(m_texture_storage.begin()->second);
    }

    return &(it->second);
}
}; // namespace kusengine::render
