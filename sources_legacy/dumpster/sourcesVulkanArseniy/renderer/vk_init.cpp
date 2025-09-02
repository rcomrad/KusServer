#include "vk_init.hpp"

#include <fstream>
#include <iostream>

#include "dds_structs.hpp"
#include "defines.h"
#include "vk_renderer.hpp"
#include "vk_types.hpp"
#include "vk_util.hpp"

VkCommandBufferBeginInfo
cmd_begin_info()
{
    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    return begin_info;
}

VkCommandBufferAllocateInfo
cmd_alloc_info(VkCommandPool pool)
{
    VkCommandBufferAllocateInfo info = {};
    info.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.commandBufferCount = 1;
    info.commandPool        = pool;
    info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    return info;
}

VkImageCreateInfo
image_create_info()
{
    VkImageCreateInfo image_info;
    image_info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.pNext         = nullptr;
    image_info.flags         = 0;
    image_info.imageType     = VK_IMAGE_TYPE_2D;
    image_info.format        = VK_FORMAT_R8G8B8A8_SRGB;
    image_info.extent.width  = 800;
    image_info.extent.height = 600;
    image_info.extent.depth  = 1;
    image_info.mipLevels     = 1;
    image_info.arrayLayers   = 1;
    image_info.samples       = VK_SAMPLE_COUNT_1_BIT;
    image_info.tiling        = VK_IMAGE_TILING_OPTIMAL;
    image_info.usage =
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT |
        VK_IMAGE_USAGE_SAMPLED_BIT; // Add sampled bit if you want to sample
                                    // from the image in a shader
    image_info.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    image_info.queueFamilyIndexCount = 0;
    image_info.pQueueFamilyIndices   = nullptr;
    image_info.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;
    return image_info;
}

char*
read_file(const std::string& filename, uint32_t& size)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file");
    }

    // Получаем размер файла
    size_t fileSize = file.tellg();
    file.seekg(0);

    // Выделяем память для буфера, который будет содержать файл
    char* buffer = new char[fileSize];

    size = fileSize;

    // Читаем данные из файла в буфер
    file.read(buffer, fileSize);
    file.close();

    return buffer; // возвращаем указатель на содержимое файла
}

VkSubmitInfo
submit_info(VkCommandBuffer* cmd, uint32_t cmdCount)
{
    VkSubmitInfo info       = {};
    info.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.commandBufferCount = cmdCount;
    info.pCommandBuffers    = cmd;

    return info;
}

VkFenceCreateInfo
fence_info(VkFenceCreateFlags flags)
{
    VkFenceCreateInfo info = {};
    info.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info.flags             = flags;
    return info;
}

VkDescriptorSetLayoutBinding
layout_binding(VkDescriptorType type, VkShaderStageFlags shaderStages,
               uint32_t count, uint32_t bindingNumber)
{
    VkDescriptorSetLayoutBinding binding = {};
    binding.binding                      = bindingNumber;
    binding.descriptorCount              = count;
    binding.descriptorType               = type;
    binding.stageFlags                   = shaderStages;

    return binding;
}

VkWriteDescriptorSet
write_set(VkDescriptorSet set, VkDescriptorType type, DescriptorInfo* descInfo,
          uint32_t bindingNumber, uint32_t count)
{
    VkWriteDescriptorSet write = {};

    write.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet          = set;
    write.pImageInfo      = &descInfo->imageInfo;
    write.pBufferInfo     = &descInfo->bufferInfo;
    write.dstBinding      = bindingNumber;
    write.descriptorCount = count;
    write.descriptorType  = type;

    return write;
}