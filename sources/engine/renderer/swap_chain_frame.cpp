#include "swap_chain_frame.hpp"

namespace kusengine
{
void
SwapChainFrame::createFrame(const vk::Device& logical_device,
                            const vk::Image& image,
                            const vk::Format& format)
{
    vk::ImageViewCreateInfo create_image_view_info = {};
    create_image_view_info.image                   = image;
    create_image_view_info.viewType                = vk::ImageViewType::e2D;
    create_image_view_info.format                  = format;
    create_image_view_info.components.r = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.components.g = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.components.b = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.components.a = vk::ComponentSwizzle::eIdentity;
    create_image_view_info.subresourceRange.aspectMask =
        vk::ImageAspectFlagBits::eColor;
    create_image_view_info.subresourceRange.baseMipLevel   = 0;
    create_image_view_info.subresourceRange.levelCount     = 1;
    create_image_view_info.subresourceRange.baseArrayLayer = 0;
    create_image_view_info.subresourceRange.layerCount     = 1;

    m_image.reset(image);
    m_view = logical_device.createImageViewUnique(create_image_view_info);
}
}; // namespace kusengine
