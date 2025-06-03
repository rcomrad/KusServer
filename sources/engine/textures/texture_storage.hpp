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

    void addTexture(std::string_view folder_path,
                    const DescriptorManager& desc_manager);

    std::optional<std::shared_ptr<Texture>> getTexture(
        std::string_view keyval) const;

private:
    TextureStorage() = default;

    std::unordered_map<std::string_view, std::shared_ptr<Texture>>
        m_texture_storage;
};

#define TEXTURE_STORAGE TextureStorage::getInstance()
}; // namespace kusengine

#endif // TEXTURE_STORAGE_HPP
