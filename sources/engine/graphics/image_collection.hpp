#pragma once

#include <vulkan/vulkan.hpp>

#include "kernel/framework/include_me.hpp"

namespace engine::graphics
{

class ImageCollection
{
public:
    ImageCollection(vk::Device& a_device,
                    vk::SwapchainKHR& a_swapchain,
                    vk::RenderPass& a_render_pass,
                    vk::Format& a_format);

    inline vk::Image getImage(int num)
    {
        SCOPED_TRACE_FUNC("getImage");
        return m_images.at(num);
    }

    inline vk::Framebuffer getFrame(int num)
    {
        SCOPED_TRACE_FUNC("getFrame");
        return *m_frame_buffers.at(num);
    }

    inline size_t size() const
    {
        return m_images.size();
    }

private:
    std::vector<vk::Image> m_images;
    std::vector<std::vector<vk::UniqueImageView>> m_image_views;
    std::vector<vk::UniqueFramebuffer> m_frame_buffers;
};

} // namespace engine::graphics
