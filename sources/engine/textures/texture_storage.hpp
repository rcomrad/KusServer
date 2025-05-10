#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP
#include <unordered_map>

#include "texture.hpp"

namespace kusengine
{
class TextureStorage
{
public:
    enum class PictureName
    {
        CAT,
        RED_TRIANGLE,
        EYE_TRIANGLE
    };

    void addTexture(std::string_view folder_path,
                    const DescriptorManager& desc_manager,
                    std::string texture_name = "");

    const Texture& getTexture(const std::string& keyval) const;

private:
    std::unordered_map<std::string, Texture> m_texture_storage;
};
}; // namespace kusengine

#endif // TEXTURE_STORAGE_HPP
