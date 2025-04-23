#include "synchronization_control.hpp"

#include "engine/device/device.hpp"
namespace kusengine
{

bool
SynchronizationControl::create()
{
    vk::SemaphoreCreateInfo semaphoreInfo = {};

    semaphoreInfo.flags = vk::SemaphoreCreateFlags();

    try
    {
        image_available =
            LOGICAL_DEVICE.createSemaphoreUnique(semaphoreInfo);
        render_finished =
            LOGICAL_DEVICE.createSemaphoreUnique(semaphoreInfo);
    }
    catch (vk::SystemError err)
    {
        return false;
    }

    vk::FenceCreateInfo fenceInfo = {};
    fenceInfo.flags =
        vk::FenceCreateFlags() | vk::FenceCreateFlagBits::eSignaled;

    try
    {
        in_flight_fence =
            LOGICAL_DEVICE.createFenceUnique(fenceInfo);
    }
    catch (vk::SystemError err)
    {
        return false;
    }
    return true;
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
}; // namespace kusengine
