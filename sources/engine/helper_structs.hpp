#ifndef HELPER_STRUCTS_HPP
#define HELPER_STRUCTS_HPP

#include <vulkan/vulkan.hpp>

struct Buffer
{
    VkBuffer m_buffer;
    VkDeviceMemory m_memory;
    void* m_data;
};

struct Image
{
    VkImage m_image;
    VkDeviceMemory m_memory;
    VkImageView m_view;
};

#endif // HELPER_STRUCTS_HPP
