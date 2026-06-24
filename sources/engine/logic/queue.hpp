#pragma once

#include <vulkan/vulkan.hpp>

#include <stdexcept>

#include "engine/logic/device.hpp"
#include "engine/typedef.hpp"

#include "base_command.hpp"
#include "one_time_command.hpp"

namespace engine::logic
{

class ResizeException : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class Queue : public vk::Queue
{
public:
    Queue(logic::Device& a_device,
          type::FamilyIndex a_queue_family,
          type::QueueIndex a_queue_index);

    uint32_t acquire_next_image(logic::Device& a_device,
                                vk::SwapchainKHR a_swapchain);

    void submit(const logic::BaseCommand& a_command_buffer);
    void submit(const std::vector<logic::BaseCommand>& a_command_buffer);

    void synchronousSubmit(OneTimeCommand& a_command);
    void present(const uint32_t& a_image_index, vk::SwapchainKHR a_swapchain);

private:
    logic::Device& m_device;

    vk::UniqueSemaphore m_present_semaphore;
    vk::UniqueSemaphore m_render_semaphore;

    void submit(const logic::BaseCommand a_command_buffers[], uint32_t a_size);

    static vk::Queue getQueue(logic::Device& a_device,
                              type::FamilyIndex a_queue_family,
                              type::QueueIndex a_queue_index);

    static void assertResult(vk::Result a_result);
};

} // namespace engine::logic
