#ifndef SYNCHRONIZATION_CONTROL_HPP
#define SYNCHRONIZATION_CONTROL_HPP

#include <vulkan/vulkan.hpp>

namespace kusengine
{
namespace render
{
class Device;

class SynchronizationControl
{
public:
    void create();

    const vk::Semaphore* const waitSemaphores() const;
    const vk::Semaphore* const signalSemaphores() const;

    const vk::Fence& inFlightFence() const;

    const vk::Semaphore& imageAvailable() const;

private:
    vk::UniqueFence in_flight_fence;
    vk::UniqueSemaphore image_available;
    vk::UniqueSemaphore render_finished;
};
}; // namespace render
}; // namespace kusengine

#endif // SYNCHRONIZATION_CONTROL_HPP
