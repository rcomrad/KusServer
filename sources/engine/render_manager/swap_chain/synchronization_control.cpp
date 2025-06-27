#include "synchronization_control.hpp"

#include "engine/render_manager/device/device.hpp"
namespace kusengine
{
namespace render
{
void
SynchronizationControl::create()
{
    vk::SemaphoreCreateInfo semaphoreInfo = {};

    semaphoreInfo.flags = vk::SemaphoreCreateFlags();

    image_available =
        LOGICAL_DEVICE_INSTANCE.createSemaphoreUnique(semaphoreInfo);
    render_finished =
        LOGICAL_DEVICE_INSTANCE.createSemaphoreUnique(semaphoreInfo);

    vk::FenceCreateInfo fenceInfo = {};
    fenceInfo.flags =
        vk::FenceCreateFlags() | vk::FenceCreateFlagBits::eSignaled;

    in_flight_fence = LOGICAL_DEVICE_INSTANCE.createFenceUnique(fenceInfo);
}


const vk::Semaphore* const
SynchronizationControl::waitSemaphores() const
{
    return &(image_available.get());
}

const vk::Semaphore* const
SynchronizationControl::signalSemaphores() const
{
    return &(render_finished.get());
}
const vk::Fence&
SynchronizationControl::inFlightFence() const
{
    return in_flight_fence.get();
}

const vk::Semaphore&
SynchronizationControl::imageAvailable() const
{
    return image_available.get();
}
}; // namespace render
}; // namespace kusengine
