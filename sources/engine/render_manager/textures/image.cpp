#include "image.hpp"

#include "engine/render_manager/device/device.hpp"
namespace kusengine
{

namespace render
{

void
Image::create(float width, float height)
{
    vk::ImageCreateInfo image_info(
        {}, vk::ImageType::e2D, vk::Format::eR8G8B8A8Unorm,
        {static_cast<uint32_t>(width), static_cast<uint32_t>(height), 1}, 1, 1,
        vk::SampleCountFlagBits::e1, vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled,
        vk::SharingMode::eExclusive);

    m_image  = LOGICAL_DEVICE_INSTANCE.createImageUnique(image_info);
    m_format = vk::Format::eR8G8B8A8Unorm;

    vk::MemoryRequirements image_mem_requirements =
        LOGICAL_DEVICE_INSTANCE.getImageMemoryRequirements(m_image.get());

    vk::MemoryAllocateInfo image_alloc_info(
        image_mem_requirements.size,
        DEVICE_INSTANCE.findMemoryTypeIndex(
            image_mem_requirements.memoryTypeBits,
            vk::MemoryPropertyFlagBits::eDeviceLocal));

    m_memory = LOGICAL_DEVICE_INSTANCE.allocateMemory(image_alloc_info);
    LOGICAL_DEVICE_INSTANCE.bindImageMemory(m_image.get(), m_memory, 0);
}

vk::ImageMemoryBarrier
Image::memoryBarrier() const
{
    return vk::ImageMemoryBarrier(
        {}, vk::AccessFlagBits::eTransferWrite, vk::ImageLayout::eUndefined,
        vk::ImageLayout::eTransferDstOptimal, VK_QUEUE_FAMILY_IGNORED,
        VK_QUEUE_FAMILY_IGNORED, m_image.get(),
        {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
}

void
Image::getDataFromBuffer(const vk::Buffer& buffer,
                         const vk::CommandBuffer& command_buffer,
                         const vk::BufferImageCopy& region)
{
    command_buffer.copyBufferToImage(buffer, m_image.get(),
                                     vk::ImageLayout::eTransferDstOptimal, 1,
                                     &region);
}

void
Image::createImageView()
{
    vk::ImageViewCreateInfo view_info(
        {}, m_image.get(), vk::ImageViewType::e2D, m_format, {},
        {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

    m_view = LOGICAL_DEVICE_INSTANCE.createImageViewUnique(view_info);
}

const vk::ImageView&
Image::view() const
{
    return m_view.get();
}
}; // namespace render
}; // namespace kusengine
