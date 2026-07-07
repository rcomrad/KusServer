#pragma once

#include <vulkan/vulkan.hpp>

#include <string>

#include "gpu/buffers/base_buffer.hpp"
#include "gpu/buffers/staging_buffer.hpp"
#include "gpu/utils/typedef.hpp"

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

    const type::SpriteSize& getSize() const;
    vk::UniqueImage&& obtainImage();

    vk::MemoryRequirements getMemReq(logic::Device& a_device) const;

private:
    std::string m_raw_data;

    type::SpriteSize m_size;
    const char* m_data;

    vk::UniqueImage m_image;

    void fillData(std::string&& a_data);
    static vk::UniqueImage createImage(logic::Device& a_device,
                                       const type::SpriteSize& a_size);
};

} // namespace gpu::sprite
