#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/command/command_pool.hpp"
#include "gpu/logic/device.hpp"
#include "gpu/logic/queue.hpp"
#include "gpu/utils/typedef.hpp"

#include "mapped_buffer.hpp"

namespace gpu::buffer
{

class StagingBuffer
{
public:
    StagingBuffer(logic::Device& a_device, vk::DeviceSize a_size);

    void transfer_image(logic::Queue& a_queue,
                        command::CommandPool& a_comm_pool,
                        vk::Image a_image,
                        const char* a_data,
                        const type::SpriteSize& a_size);

private:
    utils::LifecycleManager<MappedBuffer> m_memory;
    vk::UniqueBuffer m_buffer;

    command::OneTimeCommand prepare_command(command::CommandPool& a_comm_pool,
                                            vk::Image a_image,
                                            const vk::Extent3D& a_extend);
};

} // namespace gpu::buffer
