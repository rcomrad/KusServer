#include "texture_storage.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

#include "utility/file_system/path_storage.hpp"

using json = nlohmann::json;

namespace kusengine
{
namespace render{
TextureStorage&
TextureStorage::getInstance()
{
    static TextureStorage ts;
    return ts;
}

void
TextureStorage::loadTextures(std::string filename,
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
TextureStorage::addTexture(const std::string& file_path,
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
        auto text_ptr = std::make_shared<Texture>();
        text_ptr->loadTexture(file_path);
        text_ptr->allocDescriptorSet(
            descriptor_manager.descriptorConstructs()[1].pool.descriptorPool(),
            descriptor_manager.descriptorSetLayoutVector()[1]);

        m_texture_storage[texture_name] = text_ptr;
    }
    catch (std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
        return;
    }
}

std::optional<std::shared_ptr<const Texture>>
TextureStorage::getTexture(std::string_view keyval) const
{
    std::optional<std::shared_ptr<Texture>> res;
    auto it = m_texture_storage.find(keyval.data());
    if (it == m_texture_storage.end())
    {
        std::cout << keyval << " cant find in texture storage\n";
    }
    else
    {
        res.emplace(it.operator*().second);
    }

    return res;
}
}; // namespace render

}; // namespace kusengine
