#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include <functional>
#include <memory>

#include "base_command.hpp"
#include "command_pool.hpp"
#include "device.hpp"
#include "images_buffer.hpp"
#include "increment_buffer.hpp"
#include "queue.hpp"

namespace engine::logic
{

class Manager
{
    // using RecordCallback = std::function<void(int, logic::BaseCommand&)>;

public:
    Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage);

    void initialize();
    std::vector<logic::BaseCommand> createCommandEnv();

    uint32_t startNextTick();
    void commitNextTick(const logic::BaseCommand& a_cmd);
    // std::vector<logic::BaseCommand>& getCommandBuffers();

    Device& getCurentDevice()
    {
        return *m_device;
    }

    void collapseImagesBuffer(ImagesBuffer& a_images_buffer,
                              vk::DescriptorSetLayout a_desc_set_layout);

private:
    uint32_t m_index;
    std::shared_ptr<core::MultitypeStorage> m_obj_ref_storage;

    // at initialize
    utils::LifecycleManager<Device> m_device;
    utils::LifecycleManager<logic::ImagesBuffer> m_buffer;

    // at createCommandEnv
    utils::LifecycleManager<CommandPool> m_command_pool;
    utils::LifecycleManager<Queue> m_queue;
    // std::vector<logic::BaseCommand> m_command_buffers;
};

} // namespace engine::logic
