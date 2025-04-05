#ifndef HELPER_STRUCTS_HPP
#define HELPER_STRUCTS_HPP

#include <vulkan/vulkan.hpp>

struct Buffer
{
    vk::UniqueBuffer m_buffer;
    vk::UniqueDeviceMemory m_memory;
    void* m_data;
};

struct Image
{
    vk::UniqueImage m_image;
    vk::UniqueDeviceMemory m_memory;
    vk::UniqueImageView m_view;
};

#endif // HELPER_STRUCTS_HPP
