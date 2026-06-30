#include "staging_buffer.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

StagingBuffer::StagingBuffer(logic::Device& a_device, vk::DeviceSize a_size)

{
    SCOPED_TRACE_CREATE("staging buffer");

    vk::BufferCreateInfo create_info;
    create_info.setSize(a_size).setUsage(vk::BufferUsageFlagBits::eTransferSrc)
        // .setSharingMode(vk::SharingMode::eExclusive)
        ;
    m_buffer = a_device.createBufferUnique(create_info);

    const auto mem_req = a_device.getBufferMemoryRequirements(*m_buffer);
    m_memory.create(a_device, mem_req.size, mem_req.memoryTypeBits,
                    vk::MemoryPropertyFlagBits::eHostVisible |
                        vk::MemoryPropertyFlagBits::eHostCoherent);
    m_memory->bind(m_buffer);
}

// void
// StagingBuffer::store(const char* a_data, vk::DeviceSize a_size)
// {
//     m_buffer.push(a_data, a_size);
// }

// void
// StagingBuffer::loadToImage(vk::UniqueVkImage& a_image)
// {
//     vkCmdCopyBufferToImage(
//         cmd, vkcontext->stagingBuffer.buffer, vkcontext->image.image,
//         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

//     m_buffer.clear();
// }

void
StagingBuffer::transfer_image(logic::CommandPool& a_comm_pool,
                              logic::Queue& a_queue,
                              const char* a_data,
                              vk::UniqueImage& a_image,
                              vk::DeviceSize a_size,
                              vk::Extent3D a_extend)
{
    m_memory->push(a_data, a_size);
    auto cmd = prepare_command(a_comm_pool, a_image, a_extend);
    a_queue.synchronousSubmit(cmd);
    m_memory->clear();
}

OneTimeCommand
StagingBuffer::prepare_command(logic::CommandPool& a_comm_pool,
                               vk::UniqueImage& a_image,
                               vk::Extent3D a_extend)
{
    auto cmd = a_comm_pool.alocateOneTimeCommand();

    cmd.pushBarrierFirstWrite(a_image);

    std::vector<vk::BufferImageCopy> region;
    region.emplace_back().setImageExtent(a_extend).setImageSubresource(
        vk::ImageSubresourceLayers{vk::ImageAspectFlagBits::eColor, 0, 0, 1});
    cmd.copyBufferToImage(*m_buffer, *a_image,
                          vk::ImageLayout::eTransferDstOptimal, region);

    cmd.pushBarrierReadPostWrite(a_image);
    cmd.end();

    return cmd;
}

} // namespace engine::logic
