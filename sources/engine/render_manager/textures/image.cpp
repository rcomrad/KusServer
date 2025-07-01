#include "image.hpp"

#include "engine/render_manager/device/device.hpp"
namespace kusengine
{

namespace render
{

void
Image::create(const ImageConfigInfo& config_info)
{
    m_format = config_info.format;

    // Image
    {
        vk::ImageCreateInfo image_info{};
        image_info.imageType = vk::ImageType::e2D;
        image_info.extent =
            vk::Extent3D{config_info.width, config_info.height, 1};
        image_info.mipLevels     = 1;
        image_info.arrayLayers   = 1;
        image_info.format        = m_format;
        image_info.tiling        = vk::ImageTiling::eOptimal;
        image_info.initialLayout = vk::ImageLayout::eUndefined;
        image_info.usage         = config_info.usage_flags;
        image_info.samples       = vk::SampleCountFlagBits::e1;
        image_info.sharingMode   = vk::SharingMode::eExclusive;
        m_image = LOGICAL_DEVICE_INSTANCE.createImageUnique(image_info);
    }

    // Mem
    {
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
}

void
Image::createImageView(const ImageViewConfigInfo& config_info)
{
    vk::ImageViewCreateInfo create_image_view_info{};
    create_image_view_info.image        = m_image.get();
    create_image_view_info.viewType     = vk::ImageViewType::e2D;
    create_image_view_info.format       = m_format;
    create_image_view_info.components.r = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.components.g = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.components.b = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.components.a = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.subresourceRange.aspectMask =
        config_info.aspect_mask;
    create_image_view_info.subresourceRange.baseMipLevel   = 0;
    create_image_view_info.subresourceRange.levelCount     = 1;
    create_image_view_info.subresourceRange.baseArrayLayer = 0;
    create_image_view_info.subresourceRange.layerCount     = 1;

    m_view =
        LOGICAL_DEVICE_INSTANCE.createImageViewUnique(create_image_view_info);
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

const vk::ImageView&
Image::view() const
{
    return m_view.get();
}
}; // namespace render
}; // namespace kusengine
