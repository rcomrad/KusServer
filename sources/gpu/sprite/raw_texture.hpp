#pragma once

#include <vulkan/vulkan.hpp>

#include <string>

#include "gpu/buffers/base_buffer.hpp"
#include "gpu/buffers/staging_buffer.hpp"

namespace gpu::sprite
{

struct RawTexture
{
public:
    RawTexture(logic::Device& a_device, std::string&& a_data);

    void writeToBuffer(logic::Queue& a_queue,
                       command::CommandPool& a_comm_pool,
                       buffer::BaseBuffer& a_memory,
                       buffer::StagingBuffer& a_transfer_buff);

    int getHeight() const;
    int getWidth() const;
    vk::UniqueImage&& obtainImage();

    vk::MemoryRequirements getMemReq(logic::Device& a_device) const;

private:
    std::string m_raw_data;

    uint32_t m_height;
    uint32_t m_width;
    const char* m_data;

    vk::UniqueImage m_image;

    void fillData(std::string&& a_data);
    static vk::UniqueImage createImage(logic::Device& a_device,
                                       uint32_t m_height,
                                       uint32_t m_width);
};

} // namespace gpu::sprite
