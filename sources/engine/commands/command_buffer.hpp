#ifndef COMMAND_BUFFER_HPP
#define COMMAND_BUFFER_HPP

#include <vulkan/vulkan.hpp>

#include "command_pool.hpp"

namespace kusengine
{
class CommandBuffer
{
public:
    CommandBuffer();

    void create(const CommandPool& command_pool);

    const vk::CommandBuffer& commandBuffer() const;

private:
    vk::UniqueCommandBuffer m_command_buffer;
};
}; // namespace kusengine

#endif // COMMAND_BUFFER_HPP
