#pragma once

#include <vulkan/vulkan.hpp>

#include <string>

#include "gpu/utils/typedef.hpp"

namespace gpu
{

namespace logic
{
class Device;
class Queue;
} // namespace logic

namespace command
{
class CommandPool;
}

namespace buffer
{
class BaseBuffer;
class StagingBuffer;
} // namespace buffer

namespace sprite
{

class PixelArray;

struct RawTexture
{
public:
    RawTexture(logic::Device& a_device, PixelArray&& a_data);

    void writeToBuffer(logic::Queue& a_queue,
                       command::CommandPool& a_comm_pool,
                       buffer::BaseBuffer& a_memory,
                       buffer::StagingBuffer& a_transfer_buff);

    const type::CoordinateSize& getSize() const;
    vk::UniqueImage&& obtainImage();

    vk::MemoryRequirements getMemReq(logic::Device& a_device) const;

private:
    const char* m_data_ptr;
    type::CoordinateSize m_size;
    std::string m_allocated_buffer;

    vk::UniqueImage m_image;

    void fillData(PixelArray&& a_data);
    static vk::UniqueImage createImage(logic::Device& a_device,
                                       const type::CoordinateSize& a_size);
};

} // namespace sprite

} // namespace gpu
