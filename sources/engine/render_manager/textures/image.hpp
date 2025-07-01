#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vulkan/vulkan.hpp>

namespace kusengine
{
namespace render
{

struct ImageConfigInfo
{
    vk::Format format;
    uint32_t width;
    uint32_t height;
    vk::ImageUsageFlags usage_flags;
};

struct ImageViewConfigInfo
{
    vk::ImageAspectFlags aspect_mask;
};

class Image
{
public:
    void create(const ImageConfigInfo& config_info);

    void createImageView(const ImageViewConfigInfo& config_info);

    vk::ImageMemoryBarrier memoryBarrier() const;

    void getDataFromBuffer(const vk::Buffer& buffer,
                           const vk::CommandBuffer& command_buffer,
                           const vk::BufferImageCopy& region);

    const vk::ImageView& view() const;

private:
    vk::UniqueImage m_image;
    vk::UniqueImageView m_view;
    vk::DeviceMemory m_memory;
    vk::Format m_format;
};
}; // namespace render
}; // namespace kusengine

#endif // IMAGE_HPP
