#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include "kernel/utility/type/declaration/move_monitor.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/utils/vk_converter.hpp"
#include "gpu/utils/vulkan_move_monitor.hpp"

namespace gpu
{

namespace logic
{
class Device;
}

namespace command
{

class CommandPool;

struct CommandBufferContext
{
    logic::Device& device;
    CommandPool& command_pool;
};

struct CommandBufferDeleter
{
    static void operator()(CommandBufferContext& a_device,
                           vk::CommandBuffer& a_this) noexcept;
};

using CommandBufferBase = VulkanUniqueWrapper<vk::CommandBuffer,
                                              CommandBufferDeleter,
                                              CommandBufferContext>;

class BaseCommand : public CommandBufferBase
{
public:
    BaseCommand(logic::Device& a_device,
                CommandPool& a_parent,
                vk::CommandBuffer a_this);
    ~BaseCommand();

    HOLY_TRINITY_ONLY_MOVE(BaseCommand);

    void pushBarrierFirstWrite(vk::Image a_image);
    void pushBarrierReadPostWrite(vk::Image a_image);

    static vk::ImageSubresourceRange base2DRange();

    void begin(vk::CommandBufferUsageFlagBits a_flag);
    void end();

private:
    bool m_has_begun;
};

} // namespace command

} // namespace gpu
