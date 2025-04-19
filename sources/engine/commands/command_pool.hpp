#ifndef COMMAND_POOL_HPP
#define COMMAND_POOL_HPP

#include <vulkan/vulkan.hpp>

namespace kusengine
{
class Device;

class CommandPool
{
public:
    CommandPool(const Device& device);

    bool create();

    vk::UniqueCommandBuffer allocateCommandBuffer() const;

private:
    const Device& device_ref;

    vk::UniqueCommandPool m_command_pool;
};
}; // namespace kusengine

#endif // COMMAND_POOL_HPP
