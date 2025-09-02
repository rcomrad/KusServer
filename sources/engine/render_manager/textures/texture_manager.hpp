#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP
#include <optional>
#include <unordered_map>

#include "glm/vec2.hpp"
#include "nlohmann/json.hpp"

#include "texture_zone.hpp"

namespace kusengine::render
{

class TextureManager
{
public:
    const Texture* const getTexture(const std::string& name) const;

    void loadTextures(const DescriptorManager& desc_manager);

private:
    void addTexture(const std::string& file_path,
                    const DescriptorManager& desc_manager);

    std::unordered_map<std::string, Texture> m_texture_storage;
};

}; // namespace kusengine::render

#endif // TEXTURE_STORAGE_HPP
