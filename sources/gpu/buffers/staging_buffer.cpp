#include "staging_buffer.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

gpu::buffer::StagingBuffer::StagingBuffer(logic::Device& a_device,
                                          vk::DeviceSize a_size)

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
    m_memory->bind(*m_buffer);
}

void
gpu::buffer::StagingBuffer::transfer_image(logic::Queue& a_queue,
                                           command::CommandPool& a_comm_pool,
                                           vk::Image a_image,
                                           const char* a_data,
                                           const type::SpriteSize& a_size)
{
    const uint32_t size       = a_size.x * a_size.y * 4;
    const vk::Extent3D extend = type::createExtend3D(a_size);

    m_memory->push(a_data, size);
    auto cmd = prepare_command(a_comm_pool, a_image, extend);
    a_queue.synchronousSubmit(cmd);
    m_memory->clear();
}

gpu::command::OneTimeCommand
gpu::buffer::StagingBuffer::prepare_command(command::CommandPool& a_comm_pool,
                                            vk::Image a_image,
                                            const vk::Extent3D& a_extend)
{
    auto cmd = a_comm_pool.alocateOneTimeCommand();

    cmd.pushBarrierFirstWrite(a_image);

    std::vector<vk::BufferImageCopy> region;
    region.emplace_back().setImageExtent(a_extend).setImageSubresource(
        vk::ImageSubresourceLayers{vk::ImageAspectFlagBits::eColor, 0, 0, 1});
    cmd.copyBufferToImage(*m_buffer, a_image,
                          vk::ImageLayout::eTransferDstOptimal, region);

    cmd.pushBarrierReadPostWrite(a_image);
    cmd.end();

    return cmd;
}
