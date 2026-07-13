#include "base_command.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include <vector>

#include "gpu/logic/device.hpp"

#include "command_pool.hpp"

gpu::command::BaseCommand::BaseCommand(logic::Device& a_device,
                                       CommandPool& a_parent,
                                       vk::CommandBuffer a_this)
    : vk::CommandBuffer(a_this),
      m_has_begun(false),
      m_is_buffer_owner(true),
      m_device(a_device),
      m_command_pool(a_parent)
{
}

gpu::command::BaseCommand::~BaseCommand()
{
    if (m_is_buffer_owner)
    {
        std::vector<vk::CommandBuffer> data = {
            *static_cast<vk::CommandBuffer*>(this)};
        m_device.freeCommandBuffers(*m_command_pool, data);
    }
}

gpu::command::BaseCommand::BaseCommand(BaseCommand&& a_other) noexcept
    : vk::CommandBuffer(a_other.toBase()),
      m_has_begun(a_other.m_has_begun),
      m_is_buffer_owner(true),
      m_device(a_other.m_device),
      m_command_pool(a_other.m_command_pool)

{
    a_other.m_is_buffer_owner = false;
}

//****************************************

void
gpu::command::BaseCommand::pushBarrierFirstWrite(vk::Image a_image)
{
    std::vector<vk::ImageMemoryBarrier> barrier;
    barrier.emplace_back()
        .setImage(a_image)
        .setOldLayout(vk::ImageLayout::eUndefined)
        .setNewLayout(vk::ImageLayout::eTransferDstOptimal)
        .setSrcAccessMask({})
        .setDstAccessMask(vk::AccessFlagBits::eTransferWrite)
        .setSubresourceRange(base2DRange());

    vk::CommandBuffer::pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe,
                                       vk::PipelineStageFlagBits::eTransfer,
                                       static_cast<vk::DependencyFlags>(0), {},
                                       {}, barrier);
}

void
gpu::command::BaseCommand::pushBarrierReadPostWrite(vk::Image a_image)
{
    std::vector<vk::ImageMemoryBarrier> barrier;
    barrier.emplace_back()
        .setImage(a_image)
        .setOldLayout(vk::ImageLayout::eTransferDstOptimal)
        .setNewLayout(vk::ImageLayout::eShaderReadOnlyOptimal)
        .setSrcAccessMask(vk::AccessFlagBits::eTransferWrite)
        .setDstAccessMask(vk::AccessFlagBits::eShaderRead)
        .setSubresourceRange(base2DRange());

    vk::CommandBuffer::pipelineBarrier(
        vk::PipelineStageFlagBits::eTransfer,
        vk::PipelineStageFlagBits::eFragmentShader,
        static_cast<vk::DependencyFlags>(0), {}, {}, barrier);
}

vk::ImageSubresourceRange
gpu::command::BaseCommand::base2DRange()
{
    vk::ImageSubresourceRange range;
    range.setAspectMask(vk::ImageAspectFlagBits::eColor)
        .setLayerCount(1)
        .setLevelCount(1);
    return range;
}

//****************************************

void
gpu::command::BaseCommand::begin(vk::CommandBufferUsageFlagBits a_flag)
{
    if (m_has_begun)
    {
        THROW("Command has been already began");
    }

    m_has_begun = true;
    vk::CommandBufferBeginInfo info;
    info.setFlags(a_flag);
    vk::CommandBuffer::begin(info);
}

void
gpu::command::BaseCommand::end()
{
    if (!m_has_begun)
    {
        THROW("Command has been already ended");
    }

    m_has_begun = false;
    vk::CommandBuffer::end();
}
