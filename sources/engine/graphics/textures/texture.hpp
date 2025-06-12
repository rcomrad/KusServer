#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vulkan/vulkan.hpp>

#include <string_view>

#include "engine/graphics/buffers/staging_buffer.hpp"
#include "engine/graphics/descriptors/descriptor_manager.hpp"

#include "image.hpp"
namespace kusengine
{
class Texture
{
    friend bool operator==(const Texture& left, const Texture& right);

public:
    // const void* const data();

    void loadTexture(std::string_view file_path);

    void allocDescriptorSet(const vk::DescriptorPool&,
                            const vk::DescriptorSetLayout&);

    void bind(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const;

private:
    int m_width;
    int m_height;

    Image m_image;

    vk::UniqueSampler m_sampler;

    vk::UniqueDescriptorSet m_descriptor_set;
};

bool
operator==(const Texture& left, const Texture& right);
}; // namespace kusengine

#endif // TEXTURE_HPP
