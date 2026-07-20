#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/command/base_command.hpp"
#include "gpu/command/one_time_command.hpp"
#include "gpu/logic/device.hpp"
#include "gpu/utils/typedef.hpp"

namespace gpu::logic
{

class Queue : public vk::Queue
{
public:
    Queue(logic::Device& a_device,
          type::FamilyIndex a_queue_family,
          type::QueueIndex a_queue_index);
    HOLY_TRINITY_ONLY_MOVE(Queue);

    uint32_t acquireNextImage(logic::Device& a_device,
                              vk::SwapchainKHR a_swapchain);

    void submit(const command::BaseCommand& a_command_buffer);
    void submit(const std::vector<command::BaseCommand>& a_command_buffer);

    void synchronousSubmit(command::OneTimeCommand& a_command);
    void present(const uint32_t& a_image_index, vk::SwapchainKHR a_swapchain);

private:
    logic::Device& m_device;

    vk::UniqueSemaphore m_present_semaphore;
    vk::UniqueSemaphore m_render_semaphore;

    void submit(const command::BaseCommand a_command_buffers[],
                uint32_t a_size);

    static vk::Queue getQueue(logic::Device& a_device,
                              type::FamilyIndex a_queue_family,
                              type::QueueIndex a_queue_index);

    static void assertResult(vk::Result a_result);
};

} // namespace gpu::logic
