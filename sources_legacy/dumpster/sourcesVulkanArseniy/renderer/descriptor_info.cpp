#include "vk_types.hpp"

DescriptorInfo::DescriptorInfo(VkSampler sampler, VkImageView imageView)
{
    imageInfo.sampler     = sampler;
    imageInfo.imageView   = imageView;
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

DescriptorInfo::DescriptorInfo(VkBuffer buffer)
{
    bufferInfo.buffer = buffer;
    bufferInfo.offset = 0;
    bufferInfo.range  = VK_WHOLE_SIZE;
}

DescriptorInfo::DescriptorInfo(VkBuffer buffer, uint32_t offset, uint32_t range)
{
    bufferInfo.buffer = buffer;
    bufferInfo.offset = offset;
    bufferInfo.range  = range;
}