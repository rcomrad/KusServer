#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/command/command_pool.hpp"
#include "gpu/logic/device.hpp"
#include "gpu/logic/queue.hpp"

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
                        uint32_t a_height,
                        uint32_t a_width);

private:
    utils::LifecycleManager<MappedBuffer> m_memory;
    vk::UniqueBuffer m_buffer;

    command::OneTimeCommand prepare_command(command::CommandPool& a_comm_pool,
                                            vk::Image a_image,
                                            const vk::Extent3D& a_extend);
};

} // namespace gpu::buffer
