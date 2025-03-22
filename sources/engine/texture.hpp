#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// #include <vulkan/vulkan.hpp>
#include "dds_structs.hpp"
#include "device.hpp"

namespace kusengine
{
class Texture
{
public:
    void loadTextureFromFile(std::string_view filename,
                             Device& device,
                             DDSFile*& data,
                             uint32_t& file_size);

private:
    VkImage m_texture;
    VkDeviceMemory m_memory;
};
}; // namespace kusengine
#endif // TEXTURE_HPP
