#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP

#include <string>
#include <unordered_map>

#include "dds_structs.hpp"
#include "device.hpp"
#include "helper_structs.hpp"

namespace kusengine
{
class TextureStorage
{
public:
    void loadTextures(Device* device_ptr);

    VkImageView getTexture(std::string_view key);

    uint32_t getTextureCount();

private:
    Device* m_device_ptr;

    void addTexture(std::string_view path);

    void createStagingBuffer();
    void destroyStagingBuffer();

    VkExtent3D createTexture(std::string_view path, Image* image_ptr);
    void allocateMemoryForTexture(Image* image_ptr);
    void copyDataFromStagingBufferToImage(VkExtent3D& extent, Image* image_ptr);
    void createImageView(Image* image_ptr);

    Buffer m_staging_buffer;
    std::unordered_map<std::string, Image> m_textures;
};
}; // namespace kusengine

#endif // TEXTURE_STORAGE_HPP
