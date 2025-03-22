#include "texture_storage.hpp"

#include "engine_util.hpp"

namespace kusengine
{
void
TextureStorage::loadTextures(Device& device)
{
    createStagingBuffer(device);

    std::string_view eye_texture_path = "resource/engine_textures/eye.dds";

    uint32_t texture_size;

    DDSFile* file_data = NULL;

    auto vec     = (engine_util::readFile(eye_texture_path));
    file_data    = (DDSFile*)vec.data();
    texture_size = file_data->header.Width * file_data->header.Height * 4;
    m_data       = memcpy(m_data, file_data, texture_size);
    // TODO: Assertions

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

    vkCreateImage(device.device(), &image_info, 0, &m_image);

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(device.device(), m_image, &mem_req);

    VkMemoryAllocateInfo alloc_info{};
    alloc_info.sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize = mem_req.size;

    alloc_info.memoryTypeIndex = device.findMemoryType(
        mem_req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(device.device(), &alloc_info, 0, &m_memory);

    vkBindImageMemory(device.device(), m_image, m_memory, 0);

    VkCommandBuffer command_buffer{};

    VkCommandBufferAllocateInfo cmd_alloc_info{};
    cmd_alloc_info.sType       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_alloc_info.level       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_alloc_info.commandPool = device.getCommandPool();
    cmd_alloc_info.commandBufferCount = 1;
    vkAllocateCommandBuffers(device.device(), &cmd_alloc_info, &command_buffer);

    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(command_buffer, &begin_info);
    // Transition Layout to Transfer optimal
    VkImageSubresourceRange range      = {};
    range.aspectMask                   = VK_IMAGE_ASPECT_COLOR_BIT;
    range.layerCount                   = 1;
    range.levelCount                   = 1;
    VkImageMemoryBarrier imgMemBarrier = {};
    imgMemBarrier.sType                = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imgMemBarrier.image                = m_image;
    imgMemBarrier.oldLayout            = VK_IMAGE_LAYOUT_UNDEFINED;
    imgMemBarrier.newLayout            = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    imgMemBarrier.srcAccessMask        = VK_ACCESS_TRANSFER_READ_BIT;
    imgMemBarrier.dstAccessMask        = VK_ACCESS_TRANSFER_WRITE_BIT;
    imgMemBarrier.subresourceRange     = range;

    vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, 0, 0, 0, 1,
                         &imgMemBarrier);

    VkBufferImageCopy copy_region{};
    copy_region.imageExtent = {file_data->header.Width,
                               file_data->header.Height, 1};

    copy_region.imageSubresource.layerCount = 1;
    copy_region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

    vkCmdCopyBufferToImage(command_buffer, m_staging_buffer, m_image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1,
                           &copy_region);

    imgMemBarrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    imgMemBarrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imgMemBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    imgMemBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, 0, 0, 0,
                         1, &imgMemBarrier);

    vkEndCommandBuffer(command_buffer);

    vkDeviceWaitIdle(device.device());

    createImageView(device);
}

VkImageView
TextureStorage::view()
{
    return m_view;
}

void
TextureStorage::createImageView(Device& device)
{
    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image                 = m_image;
    viewInfo.format                = VK_FORMAT_R8G8B8A8_UNORM;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.layerCount = 1;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.viewType                    = VK_IMAGE_VIEW_TYPE_2D;

    vkCreateImageView(device.device(), &viewInfo, 0, &m_view);
}

void
TextureStorage::createStagingBuffer(Device& device)
{

    VkDeviceSize dev_size            = 1024 * 1024 * 20;
    VkBufferUsageFlags flags         = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkMemoryPropertyFlags prop_flags = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
                                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

    device.createBuffer(dev_size, flags, prop_flags, m_staging_buffer,
                        m_staging_buffer_memory);

    vkMapMemory(device.device(), m_staging_buffer_memory, 0, dev_size, 0,
                &m_data);
}

}; // namespace kusengine
