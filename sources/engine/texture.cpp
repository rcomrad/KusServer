#include "texture.hpp"

#include <fstream>
#include <iostream>

#include "utility/file_system/path_storage.hpp"

#include "dds_structs.hpp"
#include "engine_util.hpp"

namespace kusengine
{

void
Texture::loadTextureFromFile(std::string_view filename,
                             Device& device,
                             DDSFile*& data,
                             uint32_t& file_size)
{
    auto vec = (engine_util::readFile(filename));
    data     = (DDSFile*)vec.data();

    // TODO: Assertions

    VkImageCreateInfo image_info{};
    image_info.sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.mipLevels   = 1;
    image_info.arrayLayers = 1;
    image_info.imageType   = VK_IMAGE_TYPE_2D;
    image_info.format      = VK_FORMAT_R8G8B8A8_UNORM;
    image_info.extent      = {data->header.Width, data->header.Height, 1};
    image_info.samples     = VK_SAMPLE_COUNT_1_BIT;
    image_info.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    vkCreateImage(device.device(), &image_info, 0, &m_texture);

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(device.device(), m_texture, &mem_req);

    // m_size = data->header.Width * data->header.Height * 4;
    file_size = data->header.Width * data->header.Height * 4;

    VkMemoryAllocateInfo alloc_info{};
    alloc_info.sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize = mem_req.size;

    alloc_info.memoryTypeIndex = device.findMemoryType(
        mem_req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(device.device(), &alloc_info, 0, &m_memory);

    vkBindImageMemory(device.device(), m_texture, m_memory, 0);
}

}; // namespace kusengine
