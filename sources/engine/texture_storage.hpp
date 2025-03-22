#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP

#include <string>
#include <unordered_map>

#include "texture.hpp"

namespace kusengine
{
class TextureStorage
{
public:
    void loadTextures(Device& device);

    VkImageView view();

private:
    void createStagingBuffer(Device& device);

    void createImageView(Device& device);

    VkBuffer m_staging_buffer;
    VkDeviceMemory m_staging_buffer_memory;
    void* m_data;

    VkImage m_image;
    VkDeviceMemory m_memory;
    VkImageView m_view;
};
}; // namespace kusengine

#endif // TEXTURE_STORAGE_HPP
