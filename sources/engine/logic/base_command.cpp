#include "base_command.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include <vector>

#include "command_pool.hpp"

namespace engine::logic
{

BaseCommand::BaseCommand(logic::Device& a_device,
                         logic::CommandPool& a_parent,
                         vk::CommandBuffer a_this)
    : vk::CommandBuffer(a_this),
      m_has_begun(false),
      m_is_buffer_owner(true),
      m_device(a_device),
      m_command_pool(a_parent)
{
}

BaseCommand::~BaseCommand()
{
    if (m_is_buffer_owner)
    {
        std::vector<vk::CommandBuffer> data = {
            *static_cast<vk::CommandBuffer*>(this)};
        m_device.freeCommandBuffers(*m_command_pool, data);
    }
}

// BaseCommand::BaseCommand(const BaseCommand& a_other)
BaseCommand::BaseCommand(BaseCommand&& a_other) noexcept
    : vk::CommandBuffer(a_other.toBase()),
      m_has_begun(a_other.m_has_begun),
      m_is_buffer_owner(true),
      m_device(a_other.m_device),
      m_command_pool(a_other.m_command_pool)

{
    a_other.m_is_buffer_owner = false;
}

// BaseCommand& BaseCommand::operator=(const BaseCommand& a_other)
// BaseCommand&
// BaseCommand::operator=(BaseCommand&& a_other) noexcept
// {
//     // TODO: remove?
//     if (this == &a_other)
//     {
//         THROW("self-assignment");
//     }

//     vk::CommandBuffer::operator=(a_other);

//     a_other.m_is_buffer_owner = false;
//     return *this;
// }

//****************************************

void
BaseCommand::pushBarrierFirstWrite(vk::UniqueImage& a_image)
{
    std::vector<vk::ImageMemoryBarrier> barrier;
    barrier.emplace_back()
        .setImage(*a_image)
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
BaseCommand::pushBarrierReadPostWrite(vk::UniqueImage& a_image)
{
    std::vector<vk::ImageMemoryBarrier> barrier;
    barrier.emplace_back()
        .setImage(*a_image)
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
BaseCommand::base2DRange()
{
    vk::ImageSubresourceRange range;
    range.setAspectMask(vk::ImageAspectFlagBits::eColor)
        .setLayerCount(1)
        .setLevelCount(1);
    return range;
}

//****************************************

void
BaseCommand::begin(vk::CommandBufferUsageFlagBits a_flag)
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
BaseCommand::end()
{
    if (!m_has_begun)
    {
        THROW("Command has been already ended");
    }

    m_has_begun = false;
    vk::CommandBuffer::end();
}

} // namespace engine::logic

// void
// foo(logic::ComandPool& a_comm_pool)
// {
//     auto comm = a_comm_pool.alocateBuffer();
//     vk::CommandBufferBeginInfo info;
//     comm->begin(info);

//     // Transition Layout to Transfer optimal

//     vk::BufferImageCopy region;
//     region.setImageExtent({data->header.Width, data->header.Height, 1})
//         .setImageSubresource.layerCount(1)
//         .setImageSubresource.aspectMask(vk::ImageAspectFlagBits::eColor);

//     cmd->copyBufferToImage();
// }

// vkCmdCopyBufferToImage(cmd,
//                        vkcontext->stagingBuffer.buffer,
//                        vkcontext->image.image,
//                        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
//                        1,
//                        &copyRegion);

// VK_CHECK(vkEndCommandBuffer(cmd));

// VkFence uploadFence;
// VkFenceCreateInfo fenceInfo = fence_info();
// VK_CHECK(vkCreateFence(vkcontext->device, &fenceInfo, 0, &uploadFence));

// VkSubmitInfo submitInfo = submit_info(&cmd);
// VK_CHECK(vkQueueSubmit(vkcontext->graphicsQueue, 1, &submitInfo,
// uploadFence));

// VK_CHECK(vkWaitForFences(vkcontext->device, 1, &uploadFence, true,
// UINT64_MAX));
