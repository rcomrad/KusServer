#ifndef COMMAND_POOL_HPP
#define COMMAND_POOL_HPP

#include <vulkan/vulkan.hpp>

namespace kusengine
{
class Device;

class CommandPool
{
public:
    CommandPool() = default;

    bool create();

    vk::UniqueCommandBuffer allocateCommandBuffer() const;

private:
    vk::UniqueCommandPool m_command_pool;
};
}; // namespace kusengine

#endif // COMMAND_POOL_HPP
