#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vulkan/vulkan.hpp>

namespace kusengine
{
    namespace render{
class Image
{
public:
    Image() = default;

    void create(float width, float height);

    vk::ImageMemoryBarrier memoryBarrier() const;

    void getDataFromBuffer(const vk::Buffer& buffer,
                           const vk::CommandBuffer& command_buffer,
                           const vk::BufferImageCopy& region);

    void createImageView();

    const vk::ImageView& view() const;

private:
    vk::UniqueImage m_image;
    vk::Format m_format;
    vk::UniqueImageView m_view;
    vk::DeviceMemory m_memory;
};
}; // namespace render
}; // namespace kusengine

#endif // IMAGE_HPP
