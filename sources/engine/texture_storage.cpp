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

    VkExtent3D extent = createTexture(path, image_ptr);
    allocateMemoryForTexture(image_ptr);
    copyDataFromStagingBufferToImage(extent, image_ptr);
    createImageView(image_ptr);
}

VkExtent3D
TextureStorage::createTexture(std::string_view path, Image* image_ptr)
{
    uint32_t texture_size;

    DDSFile* file_data = NULL;

    auto vec  = (engine_util::readFile(path));
    file_data = (DDSFile*)(vec.data());

    texture_size = file_data->header.Width * file_data->header.Height * 4;

    memcpy(m_staging_buffer.m_data, file_data, texture_size);

    VkImageCreateInfo image_info{};
    image_info.sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.mipLevels   = 1;
    image_info.arrayLayers = 1;
    image_info.imageType   = VK_IMAGE_TYPE_2D;
    image_info.format      = VK_FORMAT_R8G8B8A8_UNORM;
    image_info.extent  = {file_data->header.Width, file_data->header.Height, 1};
    image_info.samples = VK_SAMPLE_COUNT_1_BIT;
    image_info.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    vkCreateImage(m_device_ptr->device(), &image_info, 0, &image_ptr->m_image);

    return image_info.extent;
}

void
TextureStorage::allocateMemoryForTexture(Image* image_ptr)
{

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(m_device_ptr->device(), image_ptr->m_image,
                                 &mem_req);

    VkMemoryAllocateInfo alloc_info{};
    alloc_info.sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize = mem_req.size;

    alloc_info.memoryTypeIndex = m_device_ptr->findMemoryType(
        mem_req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(m_device_ptr->device(), &alloc_info, 0,
                     &image_ptr->m_memory);

    vkBindImageMemory(m_device_ptr->device(), image_ptr->m_image,
                      image_ptr->m_memory, 0);
}

void
TextureStorage::copyDataFromStagingBufferToImage(VkExtent3D& extent,
                                                 Image* image_ptr)
{

    VkCommandBuffer command_buffer{};

    VkCommandBufferAllocateInfo cmd_alloc_info{};
    cmd_alloc_info.sType       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_alloc_info.level       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_alloc_info.commandPool = m_device_ptr->getCommandPool();
    cmd_alloc_info.commandBufferCount = 1;
    vkAllocateCommandBuffers(m_device_ptr->device(), &cmd_alloc_info,
                             &command_buffer);

    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(command_buffer, &begin_info);

    VkImageSubresourceRange range      = {};
    range.aspectMask                   = VK_IMAGE_ASPECT_COLOR_BIT;
    range.layerCount                   = 1;
    range.levelCount                   = 1;
    VkImageMemoryBarrier imgMemBarrier = {};
    imgMemBarrier.sType                = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imgMemBarrier.image                = image_ptr->m_image;
    imgMemBarrier.oldLayout            = VK_IMAGE_LAYOUT_UNDEFINED;
    imgMemBarrier.newLayout            = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    imgMemBarrier.srcAccessMask        = VK_ACCESS_TRANSFER_READ_BIT;
    imgMemBarrier.dstAccessMask        = VK_ACCESS_TRANSFER_WRITE_BIT;
    imgMemBarrier.subresourceRange     = range;

    vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, 0, 0, 0, 1,
                         &imgMemBarrier);

    VkBufferImageCopy copy_region{};
    copy_region.imageExtent = extent;
    //{file_data->header.Width, file_data->header.Height, 1};

    copy_region.imageSubresource.layerCount = 1;
    copy_region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

    vkCmdCopyBufferToImage(
        command_buffer, m_staging_buffer.m_buffer, image_ptr->m_image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy_region);

    imgMemBarrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    imgMemBarrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imgMemBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    imgMemBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, 0, 0, 0,
                         1, &imgMemBarrier);

    vkEndCommandBuffer(command_buffer);

    VkFence upload_fence;
    VkFenceCreateInfo fence_info{};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vkCreateFence(m_device_ptr->device(), &fence_info, 0, &upload_fence);

    VkSubmitInfo submit_info{};
    submit_info.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers    = &command_buffer;

    vkQueueSubmit(m_device_ptr->graphicsQueue(), 1, &submit_info, upload_fence);
    vkWaitForFences(m_device_ptr->device(), 1, &upload_fence, VK_TRUE,
                    UINT64_MAX);
    vkDeviceWaitIdle(m_device_ptr->device());
}

void
TextureStorage::destroyStagingBuffer()
{
    vkUnmapMemory(m_device_ptr->device(), m_staging_buffer.m_memory);
    vkDestroyBuffer(m_device_ptr->device(), m_staging_buffer.m_buffer, nullptr);
    vkFreeMemory(m_device_ptr->device(), m_staging_buffer.m_memory, nullptr);
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

VkImageView
TextureStorage::getTexture(std::string_view key)
{
    return m_textures[key.data()].m_view;
}

void
TextureStorage::createImageView(Image* image_ptr)
{
    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image                 = image_ptr->m_image;
    viewInfo.format                = VK_FORMAT_R8G8B8A8_UNORM;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.layerCount = 1;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.viewType                    = VK_IMAGE_VIEW_TYPE_2D;

    vkCreateImageView(m_device_ptr->device(), &viewInfo, 0, &image_ptr->m_view);
}

void
TextureStorage::createStagingBuffer()
{

    VkDeviceSize dev_size            = 1024 * 1024 * 20;
    VkBufferUsageFlags flags         = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkMemoryPropertyFlags prop_flags = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
                                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

    m_device_ptr->createBuffer(dev_size, flags, prop_flags,
                               m_staging_buffer.m_buffer,
                               m_staging_buffer.m_memory);

    vkMapMemory(m_device_ptr->device(), m_staging_buffer.m_memory, 0, dev_size,
                0, &m_staging_buffer.m_data);
}

}; // namespace kusengine
