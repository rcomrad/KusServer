#include "vk_util.hpp"

#include <iostream>

#include "defines.h"

Image
vk_allocate_image(VkDevice device, VkPhysicalDevice gpu, uint32_t width,
                  uint32_t height, VkFormat format)
{
    Image image                  = {};
    VkImageCreateInfo image_info = {};
    image_info.sType             = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.mipLevels         = 1;
    image_info.arrayLayers       = 1;
    image_info.imageType         = VK_IMAGE_TYPE_2D;
    image_info.format            = VK_FORMAT_R8G8B8A8_UNORM;
    image_info.extent            = {width, height, 1};
    image_info.samples           = VK_SAMPLE_COUNT_1_BIT;
    image_info.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

    VkImageCreateInfo imgInfo = {};
    imgInfo.sType             = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imgInfo.mipLevels         = 1;
    imgInfo.arrayLayers       = 1;
    imgInfo.imageType         = VK_IMAGE_TYPE_2D;
    imgInfo.format            = VK_FORMAT_R8G8B8A8_UNORM;
    imgInfo.extent            = {width, height, 1};
    imgInfo.samples           = VK_SAMPLE_COUNT_1_BIT;
    imgInfo.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    // imgInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    (vkCreateImage(device, &imgInfo, 0, &image.image));

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, image.image, &memRequirements);

    VkPhysicalDeviceMemoryProperties gpuMemProps;
    vkGetPhysicalDeviceMemoryProperties(gpu, &gpuMemProps);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize       = memRequirements.size;
    for (uint32_t i = 0; i < gpuMemProps.memoryTypeCount; i++)
    {
        if (memRequirements.memoryTypeBits & (1 << i) &&
            (gpuMemProps.memoryTypes[i].propertyFlags &
             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) ==
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
        {
            allocInfo.memoryTypeIndex = i;
        }
    }
    (vkAllocateMemory(device, &allocInfo, 0, &image.memory));
    (vkBindImageMemory(device, image.image, image.memory, 0));

    return image;
}

uint32_t
vk_get_memory_type_index(VkPhysicalDevice gpu,
                         VkMemoryRequirements memRequirements,
                         VkMemoryPropertyFlags memProps)
{
    uint32_t typeIdx = INVALID_IDX;

    VkPhysicalDeviceMemoryProperties gpuMemProps;
    vkGetPhysicalDeviceMemoryProperties(gpu, &gpuMemProps);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize       = memRequirements.size;
    for (uint32_t i = 0; i < gpuMemProps.memoryTypeCount; i++)
    {
        if (memRequirements.memoryTypeBits & (1 << i) &&
            (gpuMemProps.memoryTypes[i].propertyFlags & memProps) == memProps)
        {
            typeIdx = i;
            break;
        }
    }

    return typeIdx;
}

Buffer
vk_allocate_buffer(VkDevice device, VkPhysicalDevice gpu, uint32_t size,
                   VkBufferUsageFlags bufferUsage,
                   VkMemoryPropertyFlags memProps)
{
    Buffer buffer = {};
    buffer.size   = size;

    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType              = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.usage              = bufferUsage;
    bufferInfo.size               = size;
    (vkCreateBuffer(device, &bufferInfo, 0, &buffer.buffer));

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer.buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize       = memRequirements.size;
    allocInfo.memoryTypeIndex =
        vk_get_memory_type_index(gpu, memRequirements, memProps);

    (vkAllocateMemory(device, &allocInfo, 0, &buffer.memory));

    // Only map memory we can actually write to from the CPU
    if (memProps & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
        (vkMapMemory(device, buffer.memory, 0, memRequirements.size, 0,
                     &buffer.data));
    }

    (vkBindBufferMemory(device, buffer.buffer, buffer.memory, 0));

    return buffer;
}
