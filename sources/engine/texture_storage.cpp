#include "texture_storage.hpp"

#include "utility/file_system/path.hpp"
#include "utility/file_system/path_storage.hpp"

#include "engine_util.hpp"

namespace kusengine
{

void
TextureStorage::addTexture(std::string_view path)
{
    DECLARE_LOCAL_CONTEXT;
    std::string name = util::Path::getName(path, LOCAL_CONTEXT);
    m_textures[name] = {};
    Image* image_ptr = &m_textures[name];

    vk::Extent3D extent = createTexture(path, image_ptr);
    allocateMemoryForTexture(image_ptr);
    copyDataFromStagingBufferToImage(extent, image_ptr);
    createImageView(image_ptr);
}

vk::Extent3D
TextureStorage::createTexture(std::string_view path, Image* image_ptr)
{
    uint32_t texture_size;

    DDSFile* file_data = NULL;

    auto vec  = (engine_util::readFile(path.data()));
    file_data = (DDSFile*)(vec.data());

    texture_size = file_data->header.Width * file_data->header.Height * 4;

    memcpy(m_staging_buffer.m_data, file_data, texture_size);

    vk::ImageCreateInfo image_create_info =
        vk::ImageCreateInfo()
            .setMipLevels(1)
            .setArrayLayers(1)
            .setImageType(vk::ImageType::e2D)
            .setFormat(vk::Format::eR8G8B8A8Unorm)
            .setExtent({file_data->header.Width, file_data->header.Height, 1})
            .setSamples(vk::SampleCountFlagBits::e1)
            .setUsage(vk::ImageUsageFlagBits::eTransferDst |
                      vk::ImageUsageFlagBits::eSampled)
            .setInitialLayout(vk::ImageLayout::eUndefined);

    image_ptr->m_image =
        m_device_ptr->device().createImageUnique(image_create_info);

    return image_create_info.extent;
}

void
TextureStorage::allocateMemoryForTexture(Image* image_ptr)
{

    auto mem_req = m_device_ptr->device().getImageMemoryRequirements(
        image_ptr->m_image.get());

    vk::MemoryAllocateInfo alloc_info(
        mem_req.size,
        m_device_ptr->findMemoryType(mem_req.memoryTypeBits,
                                     vk::MemoryPropertyFlagBits::eDeviceLocal));

    image_ptr->m_memory.get() =
        m_device_ptr->device().allocateMemory(alloc_info);
    m_device_ptr->device().bindImageMemory(image_ptr->m_image.get(),
                                           image_ptr->m_memory.get(), 0);
}

void
TextureStorage::copyDataFromStagingBufferToImage(const vk::Extent3D& extent,
                                                 Image* image_ptr)
{

    vk::CommandBufferAllocateInfo cmd_alloc_info(
        m_device_ptr->getCommandPool(), vk::CommandBufferLevel::ePrimary, 1);
    auto command_buffers =
        m_device_ptr->device().allocateCommandBuffers(cmd_alloc_info);
    auto command_buffer = command_buffers[0];

    vk::CommandBufferBeginInfo begin_info(
        vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

    command_buffer.begin(begin_info);

    vk::ImageMemoryBarrier transfer_barrier(
        vk::AccessFlagBits::eTransferRead,    // srcAccessMask
        vk::AccessFlagBits::eTransferWrite,   // dstAccessMask
        vk::ImageLayout::eUndefined,          // oldLayout
        vk::ImageLayout::eTransferDstOptimal, // newLayout
        VK_QUEUE_FAMILY_IGNORED,              // srcQueueFamilyIndex
        VK_QUEUE_FAMILY_IGNORED,              // dstQueueFamilyIndex
        image_ptr->m_image.get(),
        vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor,
                                  0, // baseMipLevel
                                  1, // levelCount
                                  0, // baseArrayLayer
                                  1  // layerCount
                                  ));
    command_buffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer,
                                   vk::PipelineStageFlagBits::eTransfer,
                                   vk::DependencyFlags(), nullptr, nullptr,
                                   transfer_barrier);

    vk::BufferImageCopy copy_region(
        0, 0, 0, // buffer offset, row length, image height
        vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor,
                                   0, // mipLevel
                                   0, // baseArrayLayer
                                   1  // layerCount
                                   ),
        vk::Offset3D(0, 0, 0), extent);

    command_buffer.copyBufferToImage(
        m_staging_buffer.m_buffer.get(), image_ptr->m_image.get(),
        vk::ImageLayout::eTransferDstOptimal, copy_region);

    // 5. Transition to shader read-only
    vk::ImageMemoryBarrier shader_barrier(
        vk::AccessFlagBits::eTransferWrite,      // srcAccessMask
        vk::AccessFlagBits::eShaderRead,         // dstAccessMask
        vk::ImageLayout::eTransferDstOptimal,    // oldLayout
        vk::ImageLayout::eShaderReadOnlyOptimal, // newLayout
        VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED,
        image_ptr->m_image.get(),
        vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
    command_buffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer,
                                   vk::PipelineStageFlagBits::eFragmentShader,
                                   vk::DependencyFlags(), nullptr, nullptr,
                                   shader_barrier);

    // 6. End and submit
    command_buffer.end();

    vk::Fence upload_fence = m_device_ptr->device().createFence({});

    vk::SubmitInfo submit_info({},             // waitSemaphores
                               {},             // waitDstStageMask
                               command_buffer, // commandBuffers
                               {}              // signalSemaphores
    );
    m_device_ptr->graphicsQueue().submit(submit_info, upload_fence);

    // 7. Wait for completion
    auto result =
        m_device_ptr->device().waitForFences(upload_fence, VK_TRUE, UINT64_MAX);
    if (result != vk::Result::eSuccess)
    {
        throw std::runtime_error("Failed to wait for fence");
    }

    // 8. Cleanup
    m_device_ptr->device().destroyFence(upload_fence);
    m_device_ptr->device().freeCommandBuffers(m_device_ptr->getCommandPool(),
                                              command_buffer);
}

void
TextureStorage::destroyStagingBuffer()
{
    m_device_ptr->device().unmapMemory(m_staging_buffer.m_memory.get());

    if (m_staging_buffer.m_buffer.get())
    {
        m_device_ptr->device().destroyBuffer(m_staging_buffer.m_buffer.get());
        m_staging_buffer.m_buffer.get() = nullptr;
    }

    if (m_staging_buffer.m_memory.get())
    {
        m_device_ptr->device().freeMemory(m_staging_buffer.m_memory.get());
        m_staging_buffer.m_memory.get() = nullptr;
    }
}

void
TextureStorage::loadTextures(Device* device_ptr)
{
    m_device_ptr = device_ptr;

    createStagingBuffer();

    std::string app_path =
        util::PathStorage::getFolderPath("app").value().data();

    addTexture(app_path + "resource/engine_textures/red_eye.dds");
    addTexture(app_path + "resource/engine_textures/eye.dds");
    addTexture(app_path + "resource/engine_textures/cat.dds");

    destroyStagingBuffer();
}
uint32_t
TextureStorage::getTextureCount()
{
    return m_textures.size();
}

vk::ImageView
TextureStorage::getTexture(std::string_view key)
{
    return m_textures[key.data()].m_view.get();
}

void
TextureStorage::createImageView(Image* image_ptr)
{
    vk::ImageViewCreateInfo view_info(
        {},                         // flags
        image_ptr->m_image.get(),   // image
        vk::ImageViewType::e2D,     // viewType
        vk::Format::eR8G8B8A8Unorm, // format
        {},                         // components
        {
            // subresourceRange
            vk::ImageAspectFlagBits::eColor, // aspectMask
            0,                               // baseMipLevel
            1,                               // levelCount
            0,                               // baseArrayLayer
            1                                // layerCount
        });

    image_ptr->m_view.get() = m_device_ptr->device().createImageView(view_info);
}

void
TextureStorage::createStagingBuffer()
{
    vk::DeviceSize dev_size    = 1024 * 1024 * 20;
    vk::BufferUsageFlags flags = vk::BufferUsageFlagBits::eTransferSrc;
    vk::MemoryPropertyFlags prop_flags =
        vk::MemoryPropertyFlagBits::eHostCoherent |
        vk::MemoryPropertyFlagBits::eHostVisible;

    m_device_ptr->createBuffer(dev_size, flags, prop_flags,
                               m_staging_buffer.m_buffer.get(),
                               m_staging_buffer.m_memory.get());

    m_staging_buffer.m_data = m_device_ptr->device().mapMemory(
        m_staging_buffer.m_memory.get(),
        0,                   // offset
        dev_size,            // size
        vk::MemoryMapFlags() // flags (none by default)
    );
}

}; // namespace kusengine
