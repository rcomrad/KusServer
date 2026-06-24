#include "queue.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

Queue::Queue(logic::Device& a_device,
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
Queue::getQueue(logic::Device& a_device,
                type::FamilyIndex a_queue_family,
                type::QueueIndex a_queue_index)
{
    SCOPED_TRACE_INIT("get queue");
    return a_device.getQueue(a_queue_family, a_queue_index);
}

uint32_t
Queue::acquire_next_image(logic::Device& a_device, vk::SwapchainKHR a_swapchain)
{
    SCOPED_TRACE_FUNC("acquire next image");

    auto temp = a_device.acquireNextImageKHR(a_swapchain, UINT64_MAX,
                                             *m_present_semaphore);

    assertResult(temp.result);
    uint32_t result = temp.value;
    LOG_DEBUG("Acquired image# %lu", result);
    return result;
}

void
Queue::submit(const logic::BaseCommand& a_command_buffer)
{
    submit(&a_command_buffer, 1);
}

void
Queue::submit(const std::vector<logic::BaseCommand>& a_command_buffer)
{
    submit(a_command_buffer.data(), a_command_buffer.size());
}

void
Queue::submit(const logic::BaseCommand a_command_buffers[], uint32_t a_size)
{
    SCOPED_TRACE_FUNC("submit");

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
}

void
Queue::synchronousSubmit(OneTimeCommand& a_command)
{
    vk::FenceCreateInfo fence_info;
    auto synchronous_fence = m_device.createFenceUnique(fence_info);

    std::vector<vk::SubmitInfo> sub_info;
    sub_info.emplace_back().setCommandBuffers(*a_command);

    vk::Queue::submit(sub_info, *synchronous_fence);
    m_device.waitForFences(*synchronous_fence, true, UINT64_MAX);
}

void
Queue::present(const uint32_t& a_image_index, vk::SwapchainKHR a_swapchain)
{
    SCOPED_TRACE_FUNC("present");

    static std::vector<vk::Semaphore> wait_semaphores{*m_render_semaphore};

    vk::PresentInfoKHR info;
    info.setWaitSemaphores(wait_semaphores)
        .setSwapchains(a_swapchain)
        .setPImageIndices(&a_image_index);

    auto result = vk::Queue::presentKHR(info);
    assertResult(result);
    vk::Queue::waitIdle(); // TODO: remove this workaround
}

void
Queue::assertResult(vk::Result a_result)
{
    if (a_result == vk::Result::eErrorOutOfDateKHR ||
        a_result == vk::Result::eSuboptimalKHR)
    {
        throw ResizeException("Window has been resized!");
    }
    if (a_result != vk::Result::eSuccess)
    {
        THROW("Unable to process image: %s", vk::to_string(a_result));
    }
}

} // namespace engine::logic
