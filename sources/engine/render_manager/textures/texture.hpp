#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vulkan/vulkan.hpp>

#include <string_view>

#include "engine/render_manager/buffers/staging_buffer.hpp"
#include "engine/render_manager/descriptors/descriptor_manager.hpp"

#include "image.hpp"
namespace kusengine
{
namespace render
{
class Texture
{
    friend bool operator==(const Texture& left, const Texture& right);

public:
    // const void* const data();

    void loadTexture(std::string_view file_path);

    void allocDescriptorSet(const DescriptorManager& desc_manager);

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
}; // namespace render
}; // namespace kusengine

#endif // TEXTURE_HPP
