#pragma once

#include "raw_texture.hpp"

#include "dds_structs.hpp"

gpu::sprite::RawTexture::RawTexture(logic::Device& a_device,
                                    std::string&& a_data)
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
    a_transfer_buff.transfer_image(a_queue, a_comm_pool, *m_image, m_data,
                                   m_size);
}

const gpu::type::SpriteSize&
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
gpu::sprite::RawTexture::fillData(std::string&& a_data)
{
    m_raw_data           = std::move(a_data);
    const char* temp_ptr = m_raw_data.data();
    auto& dds_file       = *reinterpret_cast<const DDSFile*>(temp_ptr);

    m_size.x = dds_file.header.width;
    m_size.y = dds_file.header.height;

    m_data = dds_file.data;
}

vk::UniqueImage
gpu::sprite::RawTexture::createImage(logic::Device& a_device,
                                     const type::SpriteSize& a_size)
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
