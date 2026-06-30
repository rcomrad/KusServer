#include "images_buffer.hpp"

#include "kernel/framework/include_me.hpp"

#include "dds_structs.hpp"

namespace engine::logic
{

ImagesBuffer::ImagesBuffer(logic::Device& a_device)
    : m_device(a_device), m_transfer_buff(a_device, 1048576) // 1 mb

{
    vk::DescriptorPoolSize pool_size;
    pool_size.setType(vk::DescriptorType::eCombinedImageSampler)
        .setDescriptorCount(1);

    vk::DescriptorPoolCreateInfo pool_info;
    pool_info.setMaxSets(1).setPoolSizeCount(1).setPPoolSizes(&pool_size);
    m_descriptor_pool = m_device.createDescriptorPoolUnique(pool_info);

    // vk::BufferCreateInfo create_info;
    // create_info.setSize(a_size).setUsage(vk::BufferUsageFlagBits::eTransferSrc)
    //     // .setSharingMode(vk::SharingMode::eExclusive)
    //     ;
    // m_buffer = m_device.createBufferUnique(create_info);

    // const auto mem_req = m_device.getBufferMemoryRequirements(*m_buffer);
    // m_memory.create(m_device, mem_req.size, mem_req.memoryTypeBits,
    //                 vk::MemoryPropertyFlagBits::eHostVisible |
    //                     vk::MemoryPropertyFlagBits::eHostCoherent);
    // m_memory->bind(m_buffer);
}

void
ImagesBuffer::push(const std::filesystem::path& a_path)
{
    auto& cur_texture = m_prepared_data.emplace_back();

    cur_texture.dds_file = core::FileReader::readFile(a_path);

    const char* ptr = cur_texture.dds_file.data();
    auto& dds_file  = *reinterpret_cast<const DDSFile*>(ptr);

    cur_texture.height    = dds_file.header.height;
    cur_texture.width     = dds_file.header.width;
    cur_texture.file_data = dds_file.data;
    cur_texture.name      = a_path.filename().string();

    // uint32_t size = cur_texture.width * cur_texture.height * 4;

    vk::ImageCreateInfo info;
    info.setMipLevels(1)
        .setArrayLayers(1)
        .setImageType(vk::ImageType::e2D)
        .setFormat(vk::Format::eR8G8B8A8Unorm)
        .setExtent({cur_texture.width, cur_texture.height, 1})
        .setSamples(vk::SampleCountFlagBits::e1)
        .setUsage(vk::ImageUsageFlagBits::eTransferDst |
                  vk::ImageUsageFlagBits::eSampled);

    cur_texture.image = m_device.createImageUnique(info);
}

void
ImagesBuffer::collapse(logic::CommandPool& a_comm_pool,
                       logic::Queue& a_queue,
                       vk::DescriptorSetLayout a_desc_set_layout)
{
    // allocate
    vk::DeviceSize total_size          = 0;
    type::MemoryTypeBits total_filters = ~0;
    for (int i = 0; i < m_prepared_data.size(); ++i)
    {
        const auto& cur = m_prepared_data[i];

        const auto mem_req = m_device.getImageMemoryRequirements(*cur.image);
        total_size += mem_req.size;
        total_filters &= mem_req.memoryTypeBits;

        if (!total_filters)
        {
            THROW("Can't store all images in one buffer: no sutable memory "
                  "type after adding image #%d.",
                  i);
        }
    }

    if (!total_size)
    {
        THROW("Textures are not loaded");
    }

    m_memory.create(m_device, total_size, total_filters,
                    vk::MemoryPropertyFlagBits::eDeviceLocal);

    // bind
    for (auto& cur : m_prepared_data)
    {
        m_memory->bind(cur.image);

        const uint32_t size = cur.width * cur.height * 4;
        m_transfer_buff.transfer_image(a_comm_pool, a_queue, cur.file_data,
                                       cur.image, size,
                                       {cur.width, cur.height, 1});

        vk::ImageViewCreateInfo view_info;
        view_info.setImage(*cur.image)
            .setViewType(vk::ImageViewType::e2D)
            .setFormat(vk::Format::eR8G8B8A8Unorm)
            // .setComponents(component)
            .setSubresourceRange({vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
        auto view = m_device.createImageViewUnique(view_info);

        vk::SamplerCreateInfo sampler_info;
        sampler_info.setMinFilter(vk::Filter::eNearest)
            .setMagFilter(vk::Filter::eNearest);
        auto sampler = m_device.createSamplerUnique(sampler_info);

        vk::DescriptorSetAllocateInfo desc_set_alloc_info;
        desc_set_alloc_info.setPSetLayouts(&a_desc_set_layout)
            .setDescriptorSetCount(1)
            .setDescriptorPool(*m_descriptor_pool);
        auto desc_set = m_device.allocateDescriptorSets(desc_set_alloc_info)[0];

        std::vector<vk::DescriptorImageInfo> desc_img_info;
        desc_img_info.emplace_back()
            .setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal)
            .setImageView(*view)
            .setSampler(*sampler);

        std::vector<vk::WriteDescriptorSet> write_desc_set;
        write_desc_set.emplace_back()
            .setDstSet(desc_set)
            .setImageInfo(desc_img_info)
            .setDstBinding(0)
            .setDescriptorCount(1)
            .setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        m_device.updateDescriptorSets(write_desc_set, {});

        m_textures.emplace(std::move(cur.name),
                           Texture{std::move(cur.image), std::move(view),
                                   std::move(sampler), desc_set});
    }
}

} // namespace engine::logic

// VK_CHECK(vkBindImageMemory(vkcontext->device,
//                            vkcontext->image.image,
//                            vkcontext->image.memory,
//                            0));

// void
// foo(logic::ComandPool& a_comm_pool)
// {
//     auto comm = a_comm_pool.alocateBuffer();
//     vk::CommandBufferBeginInfo info;
//     comm->begin(info);

//     vk::ImageSubresourceRange range;
//     range.setAspectMask(ImageAspectFlagBits::eColor)
//         .setLayerCount(1)
//         .setLevelCount(1);

//     // Transition Layout to Transfer optimal
//     std::vector<vk::ImageMemoryBarrier> barrier;
//     barrier.eplace_back()
//         .setImage(image)
//         .setOldLayout(vk::ImageLayout::eUndefined)
//         .setNewLayout(vk::ImageLayout::eTransferDstOptimal)
//         .setSrcAccessMask(vk::AccessFlagBits::eTransferRead)
//         .setDstAccessMask(vk::AccessFlagBits::eTransferWrite)
//         .setSubresourceRange(range);

//     cmd.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer,
//                         vk::PipelineStageFlagBits::eTransfer, 0, {}, {},
//                         barrier);

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

// imgMemBarrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
// imgMemBarrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
// imgMemBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
// imgMemBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

// vkCmdPipelineBarrier(cmd,
//                      VK_PIPELINE_STAGE_TRANSFER_BIT,
//                      VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
//                      0,
//                      0,
//                      0,
//                      0,
//                      0,
//                      1,
//                      &imgMemBarrier);

// VK_CHECK(vkEndCommandBuffer(cmd));

// VkFence uploadFence;
// VkFenceCreateInfo fenceInfo = fence_info();
// VK_CHECK(vkCreateFence(vkcontext->device, &fenceInfo, 0, &uploadFence));

// VkSubmitInfo submitInfo = submit_info(&cmd);
// VK_CHECK(vkQueueSubmit(vkcontext->graphicsQueue, 1, &submitInfo,
// uploadFence));

// VK_CHECK(vkWaitForFences(vkcontext->device, 1, &uploadFence, true,
// UINT64_MAX));
