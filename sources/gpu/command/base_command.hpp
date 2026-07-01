#pragma once

#include <vulkan/vulkan.hpp>

#include "gpu/logic/device.hpp"

namespace gpu::command
{

class CommandPool;

class BaseCommand : public vk::CommandBuffer
{
public:
    BaseCommand(logic::Device& a_device,
                CommandPool& a_parent,
                vk::CommandBuffer a_this);
    ~BaseCommand();

    // BaseCommand(const BaseCommand& a_other);
    // BaseCommand& operator=(const BaseCommand& a_other);

    BaseCommand(const BaseCommand&)            = delete;
    BaseCommand& operator=(const BaseCommand&) = delete;

    BaseCommand(BaseCommand&& other) noexcept;
    BaseCommand& operator=(BaseCommand&& other) noexcept = delete;

    void pushBarrierFirstWrite(vk::Image a_image);
    void pushBarrierReadPostWrite(vk::Image a_image);

    static vk::ImageSubresourceRange base2DRange();

    void begin(vk::CommandBufferUsageFlagBits a_flag);
    void end();

    VK_CONVERTER(vk::CommandBuffer);

private:
    bool m_has_begun;
    mutable bool m_is_buffer_owner;
    logic::Device& m_device;
    CommandPool& m_command_pool;
};

} // namespace gpu::command
