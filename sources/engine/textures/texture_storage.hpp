#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP
#include <unordered_map>

#include "texture.hpp"

namespace kusengine
{
class TextureStorage
{
public:
    void addTexture(std::string_view folder_path,
                    const DescriptorManager& desc_manager);

    std::shared_ptr<Texture> getTexture(const std::string& keyval) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_texture_storage;
};
}; // namespace kusengine

#endif // TEXTURE_STORAGE_HPP
