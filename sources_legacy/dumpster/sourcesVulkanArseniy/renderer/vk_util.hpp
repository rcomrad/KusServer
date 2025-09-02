#ifndef VK_UTIL_HPP
#define VK_UTIL_HPP

#include "vk_types.hpp"

Image
vk_allocate_image(VkDevice device, VkPhysicalDevice gpu, uint32_t width,
                  uint32_t height, VkFormat format);

Buffer
vk_allocate_buffer(VkDevice device, VkPhysicalDevice gpu, uint32_t size,
                   VkBufferUsageFlags bufferUsage,
                   VkMemoryPropertyFlags memProps);

#endif // VK_UTIL_HPP