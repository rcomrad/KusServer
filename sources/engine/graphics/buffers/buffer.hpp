#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vulkan/vulkan.hpp>

#include "engine/graphics/device/device.hpp"
#include "engine/graphics/textures/image.hpp"

namespace kusengine
{
class Buffer
{
public:
    // ---------- //
    static void copyBuffer(const Buffer* const src_buffer,
                           Buffer* const dst_buffer,
                           vk::Queue queue,
                           const vk::CommandBuffer& command_buffer);

    static void copyBufferToImage(const Buffer* src_buffer,
                                  Image& dst_image,
                                  vk::Queue queue,
                                  const vk::CommandBuffer& command_buffer,
                                  float w,
                                  float h);

    // ---------- //
    Buffer(vk::BufferUsageFlags buffer_usage_flags,
           vk::MemoryPropertyFlags requested_properties);

    void recreate(const vk::DeviceSize& size);

    void checkBufferSize(const vk::DeviceSize& required_size);

    template <typename T>
    void setData(T data, const vk::DeviceSize& byte_size);

    const vk::Buffer& buffer() const;

    vk::DeviceSize byteSize() const;

private:
    void allocateBufferMemory();

    vk::UniqueBuffer m_buffer;

    vk::DeviceSize m_byte_size;

    vk::BufferUsageFlags m_buffer_usage_flags;
    vk::MemoryPropertyFlags m_requested_properties;

    vk::UniqueDeviceMemory m_memory;
};

template <typename T>
void
Buffer::setData(T data, const vk::DeviceSize& byte_size)
{
    checkBufferSize(byte_size);

    void* memory_location =
        LOGICAL_DEVICE.mapMemory(m_memory.get(), 0, m_byte_size);

    memcpy(memory_location, data, m_byte_size);

    LOGICAL_DEVICE.unmapMemory(m_memory.get());
}

}; // namespace kusengine

#endif // BUFFER_HPP
