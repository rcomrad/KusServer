#pragma once

#include <vulkan/vulkan.hpp>

#include "gpu/logic/device.hpp"

namespace gpu::buffer
{

class BaseBuffer
{
public:
    BaseBuffer(logic::Device& a_device,
               vk::DeviceSize a_size,
               type::MemoryTypeBits a_type_filter,
               vk::MemoryPropertyFlags a_properties);

    void bind(vk::Buffer a_buffer);
    void bind(vk::Image a_image);

protected:
    char* mapMemory();
    void unmapMemory();

private:
    logic::Device& m_device;
    vk::DeviceSize m_size;
    vk::DeviceSize m_cur_bind;

    vk::UniqueDeviceMemory m_allocated_memory;
};

} // namespace gpu::buffer
