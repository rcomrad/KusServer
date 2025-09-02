#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vulkan/vulkan.hpp>

#include "engine/render_manager/device/device.hpp"

namespace kusengine
{
namespace render
{

class Image;

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

    virtual void setData(void* data, const vk::DeviceSize& byte_size);

    const vk::Buffer& buffer() const noexcept;

    vk::DeviceSize byteSize() const noexcept;

private:
    void allocateBufferMemory();

    vk::UniqueBuffer m_buffer;

    vk::DeviceSize m_byte_size;

    vk::BufferUsageFlags m_buffer_usage_flags;
    vk::MemoryPropertyFlags m_requested_properties;

    vk::UniqueDeviceMemory m_memory;
};

}; // namespace render
}; // namespace kusengine

#endif // BUFFER_HPP
