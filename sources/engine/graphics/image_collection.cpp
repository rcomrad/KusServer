#include "image_collection.hpp"

#include <algorithm>

#include "kernel/framework/include_me.hpp"

namespace engine::graphics
{

ImageCollection::ImageCollection(vk::Device& a_device,
                                 vk::SwapchainKHR& a_swapchain,
                                 vk::RenderPass& a_render_pass,
                                 vk::Format& a_format)
{
    vk::ComponentMapping component(
        vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity,
        vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity);

    vk::ImageSubresourceRange subresource_range;
    subresource_range.setAspectMask(vk::ImageAspectFlagBits::eColor)
        .setBaseMipLevel(0)
        .setLevelCount(1)
        .setBaseArrayLayer(0)
        .setLayerCount(1);

    core::IntVar width("win_width");
    core::IntVar height("win_height");

    m_images = a_device.getSwapchainImagesKHR(a_swapchain);
    static std::vector<std::vector<vk::ImageView>> attachment;
    for (auto& i : m_images)
    {
        vk::ImageViewCreateInfo view_info;

        view_info.setImage(i)
            .setViewType(vk::ImageViewType::e2D)
            .setFormat(a_format)
            .setComponents(component)
            .setSubresourceRange(subresource_range);

        m_image_views.emplace_back().emplace_back(
            a_device.createImageViewUnique(view_info));

        vk::FramebufferCreateInfo frame_info;

        attachment.emplace_back().emplace_back(*m_image_views.back().back());
        frame_info.setLayers(1)
            .setAttachments(attachment.back())
            .setRenderPass(a_render_pass)
            .setWidth(width.get())
            .setHeight(height.get());

        m_frame_buffers.emplace_back(
            a_device.createFramebufferUnique(frame_info));
    }
}

} // namespace engine::graphics
