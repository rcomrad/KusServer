#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/logic/device.hpp"

namespace engine::logic
{

class BaseBuffer
{
public:
    BaseBuffer(logic::Device& a_device,
               vk::DeviceSize a_size,
               type::MemoryTypeBits a_type_filter,
               vk::MemoryPropertyFlags a_properties);

    void bind(vk::UniqueBuffer& a_buffer);
    void bind(vk::UniqueImage& a_image);

protected:
    char* mapMemory();
    void unmapMemory();

private:
    logic::Device& m_device;
    vk::DeviceSize m_size;
    vk::DeviceSize m_cur_bind;

    vk::UniqueDeviceMemory m_allocated_memory;
};

} // namespace engine::logic
