#pragma once

#include <vulkan/vulkan.hpp>

#include <stdexcept>

#include "engine/logic/device.hpp"
#include "engine/typedef.hpp"

namespace engine::logic
{

class ResizeException : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class Queue : public vk::Queue
{

public:
    Queue(logic::Device a_device,
          type::FamilyIndex a_queue_family,
          type::QueueIndex a_queue_index);

    uint32_t acquire_next_image(logic::Device a_device,
                                vk::SwapchainKHR a_swapchain);

    void submit(vk::CommandBuffer a_command_buffer, bool a_is_async = true);
    void submit(std::vector<vk::CommandBuffer> a_command_buffer,
                bool a_is_async = true);
    void present(const uint32_t& a_image_index, vk::SwapchainKHR a_swapchain);

private:
    vk::UniqueSemaphore m_present_semaphore;
    vk::UniqueSemaphore m_render_semaphore;

    static vk::Queue getQueue(logic::Device a_device,
                              type::FamilyIndex a_queue_family,
                              type::QueueIndex a_queue_index);

    static void assertResult(vk::Result a_result);
};

} // namespace engine::logic
