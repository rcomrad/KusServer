#include "queue.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "gpu/utils/exception.hpp"

gpu::logic::Queue::Queue(logic::Device& a_device,
                         type::FamilyIndex a_queue_family,
                         type::QueueIndex a_queue_index)
    : vk::Queue(getQueue(a_device, a_queue_family, a_queue_index)),
      m_device(a_device)
{
    SCOPED_TRACE_INIT("queue fences & semaphores");

    vk::SemaphoreCreateInfo sem_info;
    m_present_semaphore = a_device.createSemaphoreUnique(sem_info);
    m_render_semaphore  = a_device.createSemaphoreUnique(sem_info);
}

vk::Queue
gpu::logic::Queue::getQueue(logic::Device& a_device,
                            type::FamilyIndex a_queue_family,
                            type::QueueIndex a_queue_index)
{
    SCOPED_TRACE_INIT("get queue");
    return a_device.getQueue(a_queue_family, a_queue_index);
}

uint32_t
gpu::logic::Queue::acquireNextImage(logic::Device& a_device,
                                    vk::SwapchainKHR a_swapchain)
{
    LOG_SPAM("acquire next image");

    auto temp = a_device.acquireNextImageKHR(a_swapchain, UINT64_MAX,
                                             *m_present_semaphore);

    assertResult(temp.result);
    uint32_t result = temp.value;
    LOG_SPAM("Acquired image# %lu", result);
    return result;
}

void
gpu::logic::Queue::submit(const command::BaseCommand& a_command_buffer)
{
    submit(&a_command_buffer, 1);
}

void
gpu::logic::Queue::submit(
    const std::vector<command::BaseCommand>& a_command_buffer)
{
    submit(a_command_buffer.data(), a_command_buffer.size());
}

void
gpu::logic::Queue::submit(const command::BaseCommand a_command_buffers[],
                          uint32_t a_size)
{
    LOG_SPAM("submit");

    std::vector<vk::SubmitInfo> info;
    auto& cur = info.emplace_back()
                    .setPCommandBuffers(a_command_buffers)
                    .setCommandBufferCount(a_size);

    vk::PipelineStageFlags wait_flags =
        vk::PipelineStageFlagBits::eColorAttachmentOutput;

    std::vector<vk::Semaphore> wait_semaphores{*m_present_semaphore};
    std::vector<vk::Semaphore> signal_semaphores{*m_render_semaphore};

    cur.setPWaitDstStageMask(&wait_flags)
        .setWaitSemaphores(wait_semaphores)
        .setSignalSemaphores(signal_semaphores);

    vk::Queue::submit(info, VK_NULL_HANDLE);

    LOG_SPAM("\t end submit");
}

void
gpu::logic::Queue::synchronousSubmit(command::OneTimeCommand& a_command)
{
    vk::FenceCreateInfo fence_info;
    auto synchronous_fence = m_device.createFenceUnique(fence_info);

    std::vector<vk::SubmitInfo> sub_info;
    sub_info.emplace_back().setCommandBuffers(*a_command);

    vk::Queue::submit(sub_info, *synchronous_fence);
    auto res = m_device.waitForFences(*synchronous_fence, true, UINT64_MAX);
    if (res != vk::Result::eSuccess)
    {
        THROW("Failed to wait for fence");
    }
}

void
gpu::logic::Queue::present(const uint32_t& a_image_index,
                           vk::SwapchainKHR a_swapchain)
{
    LOG_SPAM("present");

    std::vector<vk::Semaphore> wait_semaphores{*m_render_semaphore};

    vk::PresentInfoKHR info;
    info.setWaitSemaphores(wait_semaphores)
        .setSwapchains(a_swapchain)
        .setPImageIndices(&a_image_index);

    auto result = vk::Queue::presentKHR(info);
    assertResult(result);
    vk::Queue::waitIdle(); // TODO: remove this workaround

    LOG_SPAM("\t end present");
}

void
gpu::logic::Queue::assertResult(vk::Result a_result)
{
    if (a_result == vk::Result::eErrorOutOfDateKHR ||
        a_result == vk::Result::eSuboptimalKHR)
    {
        throw utils::ResizeException();
    }
    if (a_result != vk::Result::eSuccess)
    {
        THROW("Unable to process image: %s", vk::to_string(a_result));
    }
}
