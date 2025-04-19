#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vulkan/vulkan.hpp>

#include "engine/device/device.hpp"

namespace kusengine
{
class Buffer
{
public:
    Buffer(const Device& device);

    void create(size_t size, vk::BufferUsageFlags usage);

    template <typename T>
    void setData(T data);

private:
    uint32_t findMemoryTypeIndex(uint32_t supported_memory_indices,
                                 vk::MemoryPropertyFlags requested_properties);

    void allocateBufferMemory();

    const Device& device_ref;

    vk::UniqueBuffer m_buffer;

    vk::UniqueDeviceMemory m_memory;

    size_t m_size;
};

template <typename T>
void
Buffer::setData(T data)
{
    void* memory_location =
        device_ref.logicalDeviceConstRef().mapMemory(m_memory.get(), 0, m_size);

    memcpy(memory_location, data, m_size);

    device_ref.logicalDeviceConstRef().unmapMemory(m_memory.get());
}

}; // namespace kusengine

#endif // BUFFER_HPP
