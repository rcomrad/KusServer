#include "image_collection.hpp"

#include "kernel/framework/include_me.hpp"

#include <algorithm>

#include "gpu/logic/device.hpp"
#include "gpu/utils/variable.hpp"

#include "render_pass.hpp"
#include "swap_chain.hpp"

gpu::pipeline::ImageCollection::ImageCollection(logic::Device& a_device,
                                                SwapChain& a_swapchain,
                                                RenderPass& a_render_pass,
                                                vk::Format& a_format)
{
    SCOPED_TRACE_INIT("image collection");

    vk::ComponentMapping component(
        vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity,
        vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity);

    vk::ImageSubresourceRange subresource_range;
    subresource_range.setAspectMask(vk::ImageAspectFlagBits::eColor)
        .setBaseMipLevel(0)
        .setLevelCount(1)
        .setBaseArrayLayer(0)
        .setLayerCount(1);

    core::IntVar width(VAR_NAME_FRAME_WIDTH);
    core::IntVar height(VAR_NAME_FRAME_HEIGHT);
    LOG_SPAM("height %d, width %d", height.get(), width.get());

    // m_images = a_device.getSwapchainImagesKHR(a_swapchain);
    // for (auto& image : m_images)
    for (auto& image : a_device.getSwapchainImagesKHR(*a_swapchain))
    {
        vk::ImageViewCreateInfo view_info;
        view_info.setImage(image)
            .setViewType(vk::ImageViewType::e2D)
            .setFormat(a_format)
            .setComponents(component)
            .setSubresourceRange(subresource_range);
        m_image_views.emplace_back(a_device.createImageViewUnique(view_info));

        std::vector<vk::ImageView> attachment{*m_image_views.back()};

        vk::FramebufferCreateInfo frame_info;
        frame_info.setLayers(1)
            .setAttachments(attachment)
            .setRenderPass(a_render_pass)
            .setWidth(width.get())
            .setHeight(height.get());
        m_frame_buffers.emplace_back(
            a_device.createFramebufferUnique(frame_info));
    }
}
