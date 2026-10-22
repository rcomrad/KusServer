#include "base_command.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include <vector>

#include "gpu/logic/device.hpp"

#include "command_pool.hpp"

gpu::command::BaseCommand::BaseCommand(logic::Device& a_device,
                                       CommandPool& a_parent,
                                       vk::CommandBuffer a_this)
    : CommandBufferBase(a_this, CommandBufferContext(a_device, a_parent)),
      m_has_begun(false)
{
}

void
gpu::command::CommandBufferDeleter::operator()(
    CommandBufferContext& a_context,
    vk::CommandBuffer& a_this) noexcept
{
    std::vector<vk::CommandBuffer> data = {a_this};
    a_context.device.freeCommandBuffers(a_context.command_pool, data);
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
