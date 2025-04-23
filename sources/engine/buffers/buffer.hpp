#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vulkan/vulkan.hpp>

#include "engine/device/device.hpp"

namespace kusengine
{
class Buffer
{
public:
    Buffer() = default;

    void recreate(vk::BufferUsageFlags usage, size_t size = 0);

    template <typename T>
    void setData(T data);

    virtual void checkBufferSize(size_t required_size) = 0;

protected:
    size_t size() const;

    vk::UniqueBuffer m_buffer;

private:
    uint32_t findMemoryTypeIndex(uint32_t supported_memory_indices,
                                 vk::MemoryPropertyFlags requested_properties);

    void allocateBufferMemory();

    vk::UniqueDeviceMemory m_memory;

    size_t m_size;
};

template <typename T>
void
Buffer::setData(T data)
{
    void* memory_location =
        LOGICAL_DEVICE.mapMemory(m_memory.get(), 0, m_size);

    memcpy(memory_location, data, m_size);

    LOGICAL_DEVICE.unmapMemory(m_memory.get());
}

}; // namespace kusengine

#endif // BUFFER_HPP
