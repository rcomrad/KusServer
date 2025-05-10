#include "texture_storage.hpp"

#include <iostream>

#include "utility/file_system/path_storage.hpp"
namespace kusengine
{

void
TextureStorage::addTexture(std::string_view file_path,
                           const DescriptorManager& descriptor_manager,
                           std::string texture_name)
{
    if (texture_name.empty())
    {
        texture_name = util::Path::getName(file_path, LOCAL_CONTEXT);
    }
    if (m_texture_storage.contains(texture_name))
    {
        std::cerr << texture_name << " has already been added\n";
        return;
    }
    try
    {
        m_texture_storage[texture_name].loadTexture(file_path);
        m_texture_storage[texture_name].allocDescriptorSet(
            descriptor_manager.descriptorConstructs()[1].pool.descriptorPool(),
            descriptor_manager.descriptorSetLayoutVector()[1]);
    }
    catch (std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
        return;
    }
}

const Texture&
TextureStorage::getTexture(const std::string& texture_name) const
{
    return m_texture_storage.find(texture_name).operator*().second;
}

}; // namespace kusengine
