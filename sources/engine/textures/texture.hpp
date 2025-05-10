#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vulkan/vulkan.hpp>

#include <string_view>

#include "engine/buffers/staging_buffer.hpp"
#include "engine/descriptors/descriptor_manager.hpp"

#include "image.hpp"
namespace kusengine
{
class Texture
{
public:
    const void* const data();

    void loadTexture(std::string_view file_path);

    void allocDescriptorSet(const vk::DescriptorPool&,
                            const vk::DescriptorSetLayout&);

    const vk::DescriptorSet& getDescriptorSet() const;

private:
    int m_width;
    int m_height;

    Image m_image;

    vk::UniqueSampler m_sampler;

    vk::UniqueDescriptorSet m_descriptor_set;
};
}; // namespace kusengine

#endif // TEXTURE_HPP
