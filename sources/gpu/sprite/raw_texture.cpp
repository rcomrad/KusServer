#include "raw_texture.hpp"

#include "gpu/buffers/base_buffer.hpp"
#include "gpu/buffers/staging_buffer.hpp"
#include "gpu/logic/device.hpp"
#include "gpu/logic/queue.hpp"

#include "pixel_array.hpp"

gpu::sprite::RawTexture::RawTexture(logic::Device& a_device,
                                    PixelArray&& a_data)
{
    fillData(std::move(a_data));
    m_image = createImage(a_device, m_size);
}

void
gpu::sprite::RawTexture::writeToBuffer(logic::Queue& a_queue,
                                       command::CommandPool& a_comm_pool,
                                       buffer::BaseBuffer& a_memory,
                                       buffer::StagingBuffer& a_transfer_buff)
{
    a_memory.bind(*m_image);
    a_transfer_buff.transfer_image(a_queue, a_comm_pool, *m_image, m_data_ptr,
                                   m_size);
}

const gpu::type::CoordinateSize&
gpu::sprite::RawTexture::getSize() const
{
    return m_size;
}

vk::UniqueImage&&
gpu::sprite::RawTexture::obtainImage()
{
    return std::move(m_image);
}

vk::MemoryRequirements
gpu::sprite::RawTexture::getMemReq(logic::Device& a_device) const
{
    return a_device.getImageMemoryRequirements(*m_image);
}

void
gpu::sprite::RawTexture::fillData(PixelArray&& a_data)
{
    m_data_ptr         = a_data.data_ptr;
    m_size             = std::move(a_data.size);
    m_allocated_buffer = std::move(a_data.allocated_buffer);
}

vk::UniqueImage
gpu::sprite::RawTexture::createImage(logic::Device& a_device,
                                     const type::CoordinateSize& a_size)
{
    vk::ImageCreateInfo info;
    info.setMipLevels(1)
        .setArrayLayers(1)
        .setImageType(vk::ImageType::e2D)
        .setFormat(vk::Format::eR8G8B8A8Unorm)
        .setExtent(type::createExtend3D(a_size))
        .setSamples(vk::SampleCountFlagBits::e1)
        .setUsage(vk::ImageUsageFlagBits::eTransferDst |
                  vk::ImageUsageFlagBits::eSampled);
    return a_device.createImageUnique(info);
}
