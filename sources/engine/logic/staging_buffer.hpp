#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include <vulkan/vulkan.hpp>

#include "engine/logic/command_pool.hpp"
#include "engine/logic/device.hpp"

#include "mapped_buffer.hpp"
#include "queue.hpp"

namespace engine::logic
{

class StagingBuffer
{
public:
    StagingBuffer(logic::Device& a_device, vk::DeviceSize a_size);

    // void store(const char* a_data, vk::DeviceSize a_size);
    // void loadToImage(vk::UniqueVkImage& a_image);

    void transfer_image(logic::CommandPool& a_comm_pool,
                        logic::Queue& a_queue,
                        const char* a_data,
                        vk::UniqueImage& a_image,
                        vk::DeviceSize a_size,
                        vk::Extent3D a_extend);

private:
    utils::LifecycleManager<MappedBuffer> m_memory;
    vk::UniqueBuffer m_buffer;

    OneTimeCommand prepare_command(logic::CommandPool& a_comm_pool,
                                   vk::UniqueImage& a_image,
                                   vk::Extent3D a_extend);
};

} // namespace engine::logic
