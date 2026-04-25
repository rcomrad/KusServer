#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/typedef.hpp"

namespace engine::logic
{

class Queue
{

public:
    Queue(vk::Device a_device,
          type::FamilyIndex a_queue_family,
          type::QueueIndex a_queue_index);

    uint32_t acquire_next_image(vk::Device a_device,
                                vk::SwapchainKHR a_swapchain);

    void submit(vk::CommandBuffer a_command_buffer, bool a_is_async = true);
    void submit(std::vector<vk::CommandBuffer> a_command_buffer,
                bool a_is_async = true);
    void present(const uint32_t& a_image_index, vk::SwapchainKHR a_swapchain);

private:
    vk::Queue m_queue;
    vk::UniqueSemaphore m_present_semaphore;
    vk::UniqueSemaphore m_render_semaphore;
};

} // namespace engine::logic
