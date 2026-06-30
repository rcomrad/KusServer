#pragma once

#include <vulkan/vulkan.hpp>

#include "device.hpp"

namespace engine::logic
{

class CommandPool;

class BaseCommand : public vk::CommandBuffer
{
public:
    BaseCommand(logic::Device& a_device,
                logic::CommandPool& a_parent,
                vk::CommandBuffer a_this);
    ~BaseCommand();

    // BaseCommand(const BaseCommand& a_other);
    // BaseCommand& operator=(const BaseCommand& a_other);

    BaseCommand(const BaseCommand&)            = delete;
    BaseCommand& operator=(const BaseCommand&) = delete;

    BaseCommand(BaseCommand&& other) noexcept;
    BaseCommand& operator=(BaseCommand&& other) noexcept = delete;

    void pushBarrierFirstWrite(vk::UniqueImage& a_image);
    void pushBarrierReadPostWrite(vk::UniqueImage& a_image);

    static vk::ImageSubresourceRange base2DRange();

    void begin(vk::CommandBufferUsageFlagBits a_flag);
    void end();

    VK_CONVERTER(vk::CommandBuffer);

private:
    bool m_has_begun;
    mutable bool m_is_buffer_owner;
    logic::Device& m_device;
    logic::CommandPool& m_command_pool;
};

} // namespace engine::logic
