#include "texture_storage.hpp"

#include <iostream>

#include "utility/file_system/path_storage.hpp"
namespace kusengine
{

void
TextureStorage::addTexture(std::string_view file_path,
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

std::shared_ptr<Texture>
TextureStorage::getTexture(const std::string& texture_name) const
{
    return m_texture_storage.find(texture_name).operator*().second;
}

}; // namespace kusengine
