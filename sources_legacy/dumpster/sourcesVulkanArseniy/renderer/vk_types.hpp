#ifndef VK_TYPES_HPP
#define VK_TYPES_HPP

#include <vulkan/vulkan.hpp>

struct Image
{
    VkImage image;
    VkDeviceMemory memory;
    VkImageView view;
};

struct Buffer
{
    VkBuffer buffer;
    VkDeviceMemory memory;
    uint32_t size;
    void* data;
};

struct DescriptorInfo
{
    union
    {
        VkDescriptorBufferInfo bufferInfo;
        VkDescriptorImageInfo imageInfo;
    };

    DescriptorInfo(VkSampler sampler, VkImageView imageView);

    DescriptorInfo(VkBuffer buffer);

    DescriptorInfo(VkBuffer buffer, uint32_t offset, uint32_t range);
};

#endif // VK_TYPES_HPP