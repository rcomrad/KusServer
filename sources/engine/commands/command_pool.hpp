#ifndef COMMAND_POOL_HPP
#define COMMAND_POOL_HPP

#include <vulkan/vulkan.hpp>

namespace kusengine
{
class Device;

class CommandPool
{
public:
    static CommandPool& getInstance();

    bool create();

    vk::UniqueCommandBuffer allocateCommandBuffer() const;

private:
    CommandPool() = default;

    vk::UniqueCommandPool m_command_pool;
};

#define COMMAND_POOL CommandPool::getInstance()

}; // namespace kusengine

#endif // COMMAND_POOL_HPP
