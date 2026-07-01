#pragma once

#include "raw_texture.hpp"

#include "dds_structs.hpp"

gpu::sprite::RawTexture::RawTexture(logic::Device& a_device,
                                    std::string&& a_data)
{
    fillData(std::move(a_data));
    m_image = createImage(a_device, m_height, m_width);
}

void
gpu::sprite::RawTexture::writeToBuffer(logic::Queue& a_queue,
                                       command::CommandPool& a_comm_pool,
                                       buffer::BaseBuffer& a_memory,
                                       buffer::StagingBuffer& a_transfer_buff)
{
    a_memory.bind(*m_image);
    a_transfer_buff.transfer_image(a_queue, a_comm_pool, *m_image, m_data,
                                   m_height, m_width);
}

int
gpu::sprite::RawTexture::getHeight() const
{
    return m_height;
}

int
gpu::sprite::RawTexture::getWidth() const
{
    return m_width;
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

    m_height = dds_file.header.height;
    m_width  = dds_file.header.width;
    m_data   = dds_file.data;
}

vk::UniqueImage
gpu::sprite::RawTexture::createImage(logic::Device& a_device,
                                     uint32_t m_height,
                                     uint32_t m_width)
{
    vk::ImageCreateInfo info;
    info.setMipLevels(1)
        .setArrayLayers(1)
        .setImageType(vk::ImageType::e2D)
        .setFormat(vk::Format::eR8G8B8A8Unorm)
        .setExtent({m_width, m_height, 1})
        .setSamples(vk::SampleCountFlagBits::e1)
        .setUsage(vk::ImageUsageFlagBits::eTransferDst |
                  vk::ImageUsageFlagBits::eSampled);
    return a_device.createImageUnique(info);
}
