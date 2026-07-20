#pragma once

#include "kernel/framework/include_me.hpp"
#include <vulkan/vulkan.hpp>

namespace gpu
{

namespace logic
{
class Device;
}

namespace pipeline
{

class SwapChain;
class RenderPass;

class ImageCollection
{
public:
    ImageCollection(logic::Device& a_device,
                    SwapChain& a_swapchain,
                    RenderPass& a_render_pass,
                    vk::Format& a_format);
    HOLY_TRINITY_ONLY_MOVE(ImageCollection);

    // inline vk::Image getImage(int num)
    // {
    //     SCOPED_TRACE_FUNC("getImage");
    //     return m_images.at(num);
    // }

    inline vk::Framebuffer getFrame(int num)
    {
        LOG_SPAM("getFrame %d from vector with size %d", num,
                 m_frame_buffers.size());
        return *m_frame_buffers.at(num);
    }

    inline size_t size() const
    {
        return m_image_views.size();
    }

private:
    // std::vector<vk::Image> m_images;
    std::vector<vk::UniqueImageView> m_image_views;
    std::vector<vk::UniqueFramebuffer> m_frame_buffers;
};

} // namespace pipeline

} // namespace gpu
