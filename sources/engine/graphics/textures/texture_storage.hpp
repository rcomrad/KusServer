#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP
#include <optional>
#include <unordered_map>

#include "texture.hpp"

namespace kusengine
{
class TextureStorage
{
public:
    static TextureStorage& getInstance();

    std::optional<std::shared_ptr<const Texture>> getTexture(
        std::string_view keyval) const;

    void loadTextures(std::string filename,
                      const DescriptorManager& desc_manager);

private:
    void addTexture(const std::string& file_path,
                    const DescriptorManager& desc_manager);

    TextureStorage() = default;

    std::unordered_map<std::string, std::shared_ptr<Texture>> m_texture_storage;
};

#define TEXTURE_STORAGE TextureStorage::getInstance()
}; // namespace kusengine

#endif // TEXTURE_STORAGE_HPP
